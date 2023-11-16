using System;
using System.CodeDom.Compiler;
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;

using F;

using LC;

namespace rxcg
{
	class Program
	{
		/// <summary>
		/// The codebase of the application
		/// </summary>
		public static readonly string CodeBase = _GetCodeBase();
		/// <summary>
		/// The filename of the application
		/// </summary>
		public static readonly string Filename = Path.GetFileName(CodeBase);
		/// <summary>
		/// The display name of the application
		/// </summary>
		public static readonly string Name = _GetName();
		/// <summary>
		/// The version of the application
		/// </summary>
		public static readonly Version Version = _GetVersion();
		/// <summary>
		/// The application description
		/// </summary>
		public static readonly string Description = _GetDescription();
		static int Main(string[] args)
		{
			return Run(args, Console.In, Console.Out, Console.Error);
		}
		public static int Run(string[] args,TextReader stdin, TextWriter stdout, TextWriter stderr)
		{
			int result = 0;
			string path = null;
			string size = "256";
			bool ifstale = false;
			string outH = null;
			string outC = null;
			bool stdint = false;
			bool prefix = false;
			bool nfas = false;
			bool dfas = false;
			try
			{
				if (0 == args.Length)
				{
					_PrintUsage(stderr);
					result = -1;
				}
				else if (args[0].StartsWith("/"))
				{
					throw new ArgumentException("Missing input file.");
				}
				else
				{
					// process the command line args
					path = args[0];
					for (var i = 1; i < args.Length; ++i)
					{
						switch (args[i].ToLowerInvariant())
						{
							case "/size":
								if (args.Length - 1 == i) // check if we're at the end
									throw new ArgumentException(string.Format("The parameter \"{0}\" is missing an argument", args[i].Substring(1)));
								++i; // advance 
								size = args[i];
								break;
							case "/ifstale":
								ifstale = true;
								break;
							case "/stdint":
								stdint = true;
								break;
							case "/prefix":
								prefix = true;
								break;
							case "/nfas":
								nfas = true;
								break;
							case "/dfas":
								dfas = true;
								break;
							default:
								throw new ArgumentException(string.Format("Unknown switch {0}", args[i]));
						}
					}
					// now build it
					string inputName = Path.GetFileNameWithoutExtension(path);
					outH = inputName + ".h";
					outC = inputName + ".c";
					var stale = true;
					if (ifstale && null != path)
					{
						stale = _IsStale(path, outH) || _IsStale(path, outC);
					}
					if (!stale)
					{
						stderr.WriteLine("{0} skipped building code because it was not stale.", Name);
					}
					else
					{
						if (File.Exists(outH))
						{
							File.Delete(outH);
						}
						if (File.Exists(outC))
						{
							File.Delete(outC);
						}
						using (var sh = new StreamWriter(outH))
						{
							using (var sc = new StreamWriter(outC))
							{
								stderr.WriteLine("Generating " + outH + " and " + outC + ".");
								Generator.Generate(path, size,stdint, prefix,nfas,dfas, sh, sc);
							}
						}
					}
				}
			}
			// we don't like to catch in debug mode
#if !DEBUG
			catch (Exception ex)
			{
				result = _ReportError(ex, stderr);
			}
#endif
			finally
			{
				
			}
			return result;
			
		}
#if !DEBUG
		// do our error handling here (release builds)
		static int _ReportError(Exception ex, TextWriter stderr)
		{
			//_PrintUsage(stderr);
			stderr.WriteLine("Error: {0}", ex.Message);
			return -1;
		}
#endif
		static bool _IsStale(string inputfile, string outputfile)
		{
			if (string.IsNullOrEmpty(outputfile) || string.IsNullOrEmpty(inputfile))
				return true;
			var result = true;
			// File.Exists doesn't always work right
			try
			{
				Stream stm = File.OpenRead(outputfile);
				stm.Close();
				if (File.GetLastWriteTimeUtc(outputfile) >= File.GetLastWriteTimeUtc(inputfile))
					result = false;
				
			}
			catch { }
			return result;
		}
		static string _GetCodeBase()
		{
			try { return Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName; }
			catch { return Path.Combine(Environment.CurrentDirectory, "rgcpp.exe"); }
		}
		static string _GetName()
		{
			try
			{
				foreach (var attr in Assembly.GetExecutingAssembly().CustomAttributes)
				{
					if (typeof(AssemblyTitleAttribute) == attr.AttributeType)
					{
						return attr.ConstructorArguments[0].Value as string;
					}
				}
			}
			catch { }
			return Path.GetFileNameWithoutExtension(Filename);
		}

		static Version _GetVersion()
		{
			return Assembly.GetExecutingAssembly().GetName().Version;
		}
		static string _GetDescription()
		{
			string result = null;
			foreach (Attribute ca in Assembly.GetExecutingAssembly().GetCustomAttributes())
			{
				var ada = ca as AssemblyDescriptionAttribute;
				if (null != ada && !string.IsNullOrWhiteSpace(ada.Description))
				{
					result = ada.Description;
					break;
				}
			}
			return result;
		}
		static void _PrintUsage(TextWriter w)
		{
			w.WriteLine("Usage: {0} <input> [/size <capture_size>] [/ifstale] [/stdint] [/prefix]", Path.GetFileName(CodeBase));
			if (!string.IsNullOrEmpty(Description))
			{
				w.WriteLine();
				w.WriteLine(Description);
			}
			w.WriteLine();
			w.WriteLine("<input>        The input file to use");
			w.WriteLine("<capture_size> The size of the capture");
			w.WriteLine("               buffer. Default is 256");
			w.WriteLine("<ifstale>      Only generate if source");
			w.WriteLine("               is newer than target");
			w.WriteLine("<prefix>       Generate a prefix for");
			w.WriteLine("               the match struct");
			w.WriteLine("<stdint>       Use <stdint.h>");
			w.WriteLine();
		}
	}
}
