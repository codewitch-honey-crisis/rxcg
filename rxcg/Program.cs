using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;

using F;
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
		static void Main(string[] args)
		{
			string path = null;
			string size = "256";
			string outH = null;
			string outC = null;
			if (args.Length < 1)
			{
				_PrintUsage();
				Console.Error.WriteLine("Too few arguments.");
				return;
			} else if (args.Length > 3)
			{
				_PrintUsage();
				Console.Error.WriteLine("Too many arguments.");
				return;
			}
			if (args.Length > 1) {
				if (args[1].ToLower()!="/size") {
					_PrintUsage();
					Console.Error.WriteLine("Invalid argument.");
					return;
				} else if(args.Length<3)
				{
					_PrintUsage();
					Console.Error.WriteLine("Expecting <capture_size> argument");
					return;
				}
				size = args[2];
			}
			path = args[0];
			string inputName = Path.GetFileNameWithoutExtension(path);
			outH = inputName + ".h";
			outC = inputName + ".c";
			/*if(!_IsStale(args[0],outH) && !_IsStale(args[0],outC))
			{
				Console.Error.WriteLine("Skipping generation because files haven't changed.");
				return;
			}*/
			if(File.Exists(outH))
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
					Console.Error.WriteLine("Generating " + outH + " and " + outC + ".");
					Generator.Generate(path, size, sh, sc);
				}
			}
			
		}
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
		static void _PrintUsage()
		{
			TextWriter w = Console.Error;
			w.WriteLine("Usage: {0} <input> [/size <capture_size>]",Path.GetFileName(CodeBase));
			if (!string.IsNullOrEmpty(Description))
			{
				w.WriteLine();
				w.WriteLine(Description);
			}
			w.WriteLine();
			w.WriteLine("<input>        The input file to use");
			w.WriteLine("<capture_size> The size of the capture");
			w.WriteLine("               buffer. Default is 256");
			w.WriteLine();
		}
	}
}
