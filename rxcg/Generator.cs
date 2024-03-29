﻿using F;

using LC;

using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

namespace rxcg
{
	class Generator
	{
		static FFA ParseToFA(LexRule rule, string inputFile, bool ignoreCase)
		{
			FFA fa;
			if (rule.Expression.StartsWith("\""))
			{
				var pc = LexContext.Create(rule.Expression);
				fa = FFA.Literal(UnicodeUtility.ToUtf32(pc.ParseJsonString()), rule.Id);
			}
			else
				fa = FFA.Parse(rule.Expression.Substring(1, rule.Expression.Length - 2), rule.Id, rule.ExpressionLine, rule.ExpressionColumn, rule.ExpressionPosition, inputFile);
			if (!ignoreCase)
			{
				var ic = (bool)rule.GetAttribute("ignoreCase", false);
				if (ic)
					fa = FFA.CaseInsensitive(fa, rule.Id);
			}
			else
			{
				var ic = (bool)rule.GetAttribute("ignoreCase", true);
				if (ic)
					fa = FFA.CaseInsensitive(fa, rule.Id);
			}
			return fa;
		}
		static FFA[] BuildMatchers(IList<LexRule> rules, string inputFile, bool ignoreCase)
		{
			int max = int.MinValue;
			for (int ic = rules.Count, i = 0; i < ic; ++i)
			{
				var rule = rules[i];
				if (rule.Id > max)
					max = rule.Id;
			}
			var result = new FFA[max + 1];
			foreach (var rule in rules)
			{
				result[rule.Id] = ParseToFA(rule, inputFile, ignoreCase);
			}
			return result;
		}
		static FFA[] BuildBlockEnds(IList<LexRule> rules, string inputFile, bool ignoreCase)
		{
			int max = int.MinValue;
			for (int ic = rules.Count, i = 0; i < ic; ++i)
			{
				var rule = rules[i];
				if (rule.Id > max)
					max = rule.Id;
			}
			var result = new FFA[max + 1];
			for (int ic = rules.Count, i = 0; i < ic; ++i)
			{
				var ci = ignoreCase;

				var rule = rules[i];
				var ica = rule.GetAttribute("ignoreCase");
				if (null != ica && ica is bool)
				{
					ci = (bool)ica;
				}
				var v = rule.GetAttribute("blockEnd");
				var be = v as string;
				if (!string.IsNullOrEmpty(be))
				{
					var cfa = FFA.Literal(UnicodeUtility.ToUtf32(be), 0);
					if (ci)
						cfa = FFA.CaseInsensitive(cfa, 0);
					result[rule.Id] = cfa.ToDfa();
				}
				else
				{
					var lr = v as LexRule;
					if (null != lr)
					{
						result[rule.Id] = ParseToFA(lr, inputFile, ci);
					}
				}
			}
			return result;
		}
		static List<LexRule> ParseRl(TextReader input)
		{
			var rules = new List<LexRule>();
			string line;
			while (null != (line = input.ReadLine()))
			{
				var lc = LC.LexContext.Create(line);
				lc.TrySkipCCommentsAndWhiteSpace();
				if (-1 != lc.Current)
					rules.Add(LexRule.Parse(lc));
			}
			LexRule.FillRuleIds(rules, true);
			return rules;
		}
		static int WidthBytes(int[] table)
		{
			int width = 1;
			for(int i = 0;i<table.Length;++i)
			{
				var entry = table[i];
				if(entry>32767||entry<-32768)
				{
					return 4;
				} else if(entry>127||entry<-128)
				{
					width = 2;
				}
			}
			return width;
		}
		static void GenerateMatchC(string name, int width,bool stdint, bool prefix,string size, TextWriter writer)
		{
			var stm = Assembly.GetExecutingAssembly().GetManifestResourceStream("rxcg.match.c");
			TextReader tr = new StreamReader(stm);
			var s = tr.ReadToEnd();
			s = s.Replace("BIT_WIDTH", (width * 8).ToString());
			s = s.Replace("UTYPE", width == 4 ? "UINT32" : width == 2 ? "UINT16" : "UINT8");
			s = s.Replace("TYPE2", width == 4 ? "dword" : width == 2 ? "word" : "byte");
			s = s.Replace("TYPE", width == 4 ? "INT32" : width == 1 ? "INT8" : "INT16");
			s = s.Replace("MAX_SIZE", size);
			s = ReplaceTypes(s, stdint);
			s = s.Replace("MATCH", name);
			if(prefix)
			{
				s = s.Replace("PREFIX", name + "_");
			} else
			{
				s = s.Replace("PREFIX", "");
			}

			writer.Write(s);
		}
		static void GenerateMatchBEC(string name, int width,bool stdint, bool prefix,string size, TextWriter writer)
		{
			var stm = Assembly.GetExecutingAssembly().GetManifestResourceStream("rxcg.match_be.c");
			TextReader tr = new StreamReader(stm);
			var s = tr.ReadToEnd();
			s = s.Replace("BIT_WIDTH", (width * 8).ToString());
			s = s.Replace("UTYPE", width == 4 ? "UINT32" : width == 2 ? "UINT16" : "UINT8");
			s = s.Replace("TYPE2", width == 4 ? "dword" : width == 2 ? "word" : "byte");
			s = s.Replace("TYPE", width == 4 ? "INT32" : width == 1 ? "INT8" : "INT16");
			s = s.Replace("MAX_SIZE", size);
			s = ReplaceTypes(s, stdint);
			s = s.Replace("MATCH", name);
			if (prefix)
			{
				s = s.Replace("PREFIX", name + "_");
			}
			else
			{
				s = s.Replace("PREFIX", "");
			}
			writer.Write(s);
		}
		static string ReplaceTypes(string s, bool stdint)
		{
			if (!stdint) {
				s = s.Replace("UINT8", "MATCH_uint8");
				s = s.Replace("INT8", "MATCH_int8");
				s = s.Replace("UINT16", "MATCH_uint16");
				s = s.Replace("INT16", "MATCH_int16");
				s = s.Replace("UINT32", "MATCH_uint32");
				s = s.Replace("INT32", "MATCH_int32");
			} else
			{
				s = s.Replace("UINT8", "uint8_t");
				s = s.Replace("INT8", "int8_t");
				s = s.Replace("UINT16", "uint16_t");
				s = s.Replace("INT16", "int16_t");
				s = s.Replace("UINT32", "uint32_t");
				s = s.Replace("INT32", "int32_t");
			}
			return s;
		}
		static void GenerateMatchEpilogueC(string name, bool stdint, bool prefix, TextWriter writer)
		{
			var stm = Assembly.GetExecutingAssembly().GetManifestResourceStream("rxcg.match_epilogue.c");
			TextReader tr = new StreamReader(stm);
			var s = tr.ReadToEnd();
			s=ReplaceTypes(s, stdint);
			s = s.Replace("MATCH", name);
			if (prefix)
			{
				s = s.Replace("PREFIX", name + "_");
			}
			else
			{
				s = s.Replace("PREFIX", "");
			}

			writer.Write(s);
		}
		static void GenerateMatchH(string name, int maxWidth, bool stdint,bool prefix, string size, TextWriter writer)
		{
			var stm = Assembly.GetExecutingAssembly().GetManifestResourceStream("rxcg.match.h");
			TextReader tr = new StreamReader(stm);
			var s = tr.ReadToEnd();
			s = s.Replace("TIMESTAMP", DateTime.Now.ToString());
			s = s.Replace("FILENAME", name + ".h");
			string repl;
			if(!stdint)
			{
				repl = "#ifndef INT8" + Environment.NewLine +
						"\t#define INT8 char" + Environment.NewLine +
						"\t#define UINT8 unsigned char" + Environment.NewLine +
						"\t#define INT16 short" + Environment.NewLine +
						"\t#define UINT16 unsigned short" + Environment.NewLine +
						"\t#define INT32 int" + Environment.NewLine +
						"\t#define UINT32 unsigned int" + Environment.NewLine +
						"#endif" + Environment.NewLine;
			} else
			{
				repl = "#include <stdint.h>";
			}
			s = s.Replace("INTDEFS", repl);
			s = s.Replace("UTYPE", maxWidth == 4 ? "UINT32" : maxWidth == 2 ? "UINT16" : "UINT8");
			s = s.Replace("TYPE2", maxWidth == 4 ? "dword" : maxWidth == 2 ? "word" : "byte");
			s = s.Replace("TYPE", maxWidth == 4 ? "INT32" : maxWidth == 1 ? "INT8" : "INT16");
			s = s.Replace("MAX_SIZE", size);
			s = ReplaceTypes(s, stdint);
			s = s.Replace("MATCH", name);
			if(prefix) {
				s = s.Replace("PREFIX", name + "_");
			}
			else
			{
				s = s.Replace("PREFIX", "");
			}

			writer.Write(s);
		}
		static void GenerateArrayElem(int[] table,int i, bool ischar, TextWriter writer)
		{
			if (i < table.Length - 1 && (i % 10) == 0)
			{
				writer.WriteLine();
				writer.Write("\t");
			}
			if (ischar && ((table[i]>31 && table[i]<128) || table[i]=='\t')) {
				writer.Write("\'");
				switch(table[i])
				{
					case '\'':
						writer.Write("\\\'");
						break;
					case '\"':
						writer.Write("\\\"");
						break;
					case '\t':
						writer.Write("\\t");
						break;
					case '\r':
						writer.Write("\\r");
						break;
					case '\n':
						writer.Write("\\n");
						break;
					case '\\':
						writer.Write("\\\\");
						break;
					default:
						writer.Write((char)table[i]);
						break;
				}
				writer.Write("\'");
			} else
			{
				writer.Write(table[i]);
			}
			if (i < table.Length - 1)
			{
				writer.Write(", ");
			}
		}
		static void GenerateArray(string name, string arrayName, string type, int[] table, TextWriter writer)
		{
			writer.Write("static ");
			writer.Write(type+" ");
			writer.Write(arrayName);
			writer.WriteLine("[]");
			writer.WriteLine("#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)");
			writer.WriteLine("PROGMEM");
			writer.WriteLine("#endif");
			writer.Write(" = {");
			int tlen;
			int prlen;
			int pmin;
			int pmax;
			int i,j;
			int state = 0;

			while (state < table.Length)
			{
				GenerateArrayElem(table, state, false, writer);
				state++;
				GenerateArrayElem(table, state, false, writer);
				tlen = table[state++];
				for (i = 0; i < tlen; ++i)
				{
					GenerateArrayElem(table, state, false, writer);
					state++;
					GenerateArrayElem(table, state, false, writer);
					prlen = table[state++];
					for (j = 0; j < prlen; ++j)
					{
						pmin = table[state++];
						pmax = table[state++];
						if (pmin < 128 && pmax < 128)
						{
							GenerateArrayElem(table, state-2, true, writer);
							GenerateArrayElem(table, state-1, true, writer);
						} else
						{
							GenerateArrayElem(table, state - 2, false, writer);
							GenerateArrayElem(table, state - 1, false, writer);
						}
					}
				}
			}
			
			writer.WriteLine();
			writer.WriteLine("};");

		}
		static string WidthToSignedType(string name, int width,bool stdint) {
			if (stdint)
			{
				switch (width)
				{
					case 1:
						return "int8_t";
					case 2:
						return "int16_t";
					case 4:
						return "int32_t";

				}
			} else
			{
				switch (width)
				{
					case 1:
						return name+"_int8";
					case 2:
						return name + "_int16";
					case 4:
						return name + "_int32";

				}
			}
			return null;
		}
		public static void Generate(string inputFile,string size, bool stdint, bool prefix, bool render_nfas,bool render_dfas,TextWriter headerOutput,TextWriter sourceOutput)
		{
			var name = Path.GetFileNameWithoutExtension(inputFile);
			IList<LexRule> rules;
			using (var stm = File.OpenRead(inputFile))
			{
				using(var input = new StreamReader(stm))
				{
					rules = ParseRl(input);
				}
			}
			var matchers = BuildMatchers(rules, inputFile, false);
			var blockEnds = BuildBlockEnds(rules, inputFile, false);
			var widths = new int[matchers.Length];
			var hasBEs = new bool[matchers.Length];
			var dfas = new int[matchers.Length][];
			var blockEndDfas = new int[blockEnds.Length][];
			var gen1 = false;
			var hasBE1 = false;
			var gen2 = false;
			var hasBE2 = false;
			var gen4 = false;
			var hasBE4 = false;
			FFA.DotGraphOptions dotOpts = new FFA.DotGraphOptions();
			dotOpts.HideAcceptSymbolIds = true;
			if (render_nfas)
			{
				for(var i = 0;i<rules.Count;++i)
				{
					var rule = rules[i];
					var fn = name + "_" + rule.Symbol + "_nfa.jpg";
					
					matchers[rule.Id].RenderToFile(fn,dotOpts);
				}
			}
			for (var i = 0; i < matchers.Length; ++i)
			{
				var m = matchers[i];
				var be = blockEnds[i];
				if(m!=null)
				{
					dfas[i] = m.ToDfaTable();
					var mw = WidthBytes(dfas[i]);
					var bw = 0;
					if(be!=null)
					{
						hasBEs[i] = true;
						blockEndDfas[i] = be.ToDfaTable();
						bw = WidthBytes(blockEndDfas[i]);
					} else
					{
						hasBEs[i] = false;
					}
					if(bw>mw)
					{
						mw = bw;
					}
					widths[i] = mw;
				}
			}
			if (render_dfas)
			{
				for (var i = 0; i < rules.Count; ++i)
				{
					var rule = rules[i];
					var fn = name + "_" + rule.Symbol + "_dfa.jpg";
					FFA.FromDfaTable(dfas[rule.Id]).RenderToFile(fn, dotOpts);
				}
			}
			sourceOutput.WriteLine("// {0}.c", name);
			sourceOutput.WriteLine("#include \"{0}.h\"", name);
			for (int i = 0; i < rules.Count; ++i)
			{
				var rule = rules[i];
				var dfa = dfas[rule.Id];
				var be = blockEndDfas[rule.Id];
				
				GenerateArray(name, rule.Symbol+"_dfa",WidthToSignedType(name, widths[rule.Id],stdint), dfa, sourceOutput);
				if (be != null)
				{
					GenerateArray(name, rule.Symbol+"_end_dfa", WidthToSignedType(name, widths[rule.Id], stdint), be, sourceOutput);
				}
			}
			int maxWidth = 0;

			for(var i = 0;i<widths.Length;++i)
			{
				var w = widths[i];
				if(w>maxWidth)
				{
					maxWidth = w;
				}
				switch(w)
				{
					case 1:
						if(!gen1)
						{
							bool hasBE = false;
							for(var j=0;j<hasBEs.Length;++j)
							{
								if(w==widths[j] && hasBEs[j])
								{
									hasBE = true;
									hasBE1 = true;
									break;
								}
							}
							if (hasBE)
							{
								GenerateMatchBEC(name, w, stdint, prefix, size, sourceOutput);
							}
							else
							{
								GenerateMatchC(name, w, stdint, prefix, size, sourceOutput);
							}
							gen1 = true;
						}
						break;
					case 2:
						if (!gen2)
						{
							bool hasBE = false;
							for (var j = 0; j < hasBEs.Length; ++j)
							{
								if (w == widths[j] && hasBEs[j])
								{
									hasBE = true;
									hasBE2 = true;
									break;
								}
							}
							if (hasBE)
							{
								GenerateMatchBEC(name, w, stdint, prefix, size, sourceOutput);
							}
							else
							{
								GenerateMatchC(name, w, stdint, prefix, size, sourceOutput);
							}
							gen2 = true;
						}
						break;
					case 4:
						if (!gen4)
						{
							bool hasBE = false;
							for (var j = 0; j < hasBEs.Length; ++j)
							{
								if (w == widths[j] && hasBEs[j])
								{
									hasBE = true;
									hasBE4 = true;
									break;
								}
							}
							if (hasBE)
							{
								GenerateMatchBEC(name, w, stdint, prefix, size, sourceOutput);
							}
							else
							{
								GenerateMatchC(name, w, stdint, prefix, size, sourceOutput);
							}
							gen4 = true;
						}
						break;
				}
			}
			string pfx = prefix ? (name + "_") : "";
			for (int i = 0; i < rules.Count; ++i)
			{
				var rule = rules[i];
				var width = widths[rule.Id];
				sourceOutput.Write("{2}match_t match_{1}(unsigned long long* position,{2}read_callback callback, void* callback_state) ", name, rule.Symbol,pfx);
				
				sourceOutput.WriteLine("{");
				if((width == 1 && hasBE1) || (width == 2 && hasBE2) || (width==4 && hasBE4))
				{
					sourceOutput.WriteLine("\treturn {0}_runner{3}({1}_dfa, {2}, position, callback, callback_state);", name, rule.Symbol, blockEnds[rule.Id] != null ? rule.Symbol + "_end_dfa" : "NULL", width * 8);
				} else
				{
					sourceOutput.WriteLine("\treturn {0}_runner{2}({1}_dfa, position, callback, callback_state);", name, rule.Symbol, width * 8);
				}
				sourceOutput.WriteLine("}");
			}
			GenerateMatchEpilogueC(name, stdint, prefix, sourceOutput);
			GenerateMatchH(name, maxWidth, stdint, prefix, size, headerOutput);
			headerOutput.WriteLine("#ifdef __cplusplus");
			headerOutput.WriteLine("extern \"C\" {");
			headerOutput.WriteLine("#endif");
			for (int i = 0; i < rules.Count; ++i)
			{
				var rule = rules[i];
				var width = widths[rule.Id];
				headerOutput.Write("// match the expression {0}", rule.Expression);
				if(blockEndDfas[rule.Id]!=null)
				{
					var bea = rule.GetAttribute("blockEnd");
					var s = bea as string;
					if (s == null)
					{
						var lr = bea as LexRule;
						s = lr.Expression;
					} else
					{
						// TODO: finish all escapes
						s = "\"" + s.Replace("\"", "\\\"").Replace("\t", "\\t").Replace("\r", "\\r").Replace("\n", "\\n").Replace("\\", "\\\\") + "\"";
					}
					headerOutput.Write(" (block end: {0})",s);
					
				}
				headerOutput.WriteLine();
				headerOutput.WriteLine("{2}match_t match_{1}(unsigned long long* position,{2}read_callback callback, void* callback_state);", name, rule.Symbol,pfx);
			}
			headerOutput.WriteLine("#ifdef __cplusplus");
			headerOutput.WriteLine("}");
			headerOutput.WriteLine("#endif");
			headerOutput.WriteLine("#endif");

		}
	}
}
