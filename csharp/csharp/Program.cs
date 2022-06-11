using System;
using System.Collections.Generic;
using System.IO;

namespace csharp
{
    internal class Resultaat
    {
        public string Code { get; set; }
        public string EC { get; set; }

        public string Cijfer { get; set; }

        public string NepCijfer
        {
            get
            {
                if (Cijfer.ToLower() == "o") return "11";
                if (Cijfer.ToLower() == "v") return "12";
                if (Cijfer.ToLower() == "v") return "13";
                return Cijfer;
            }
            set { Cijfer = value; }
        }
    }

    internal class Program
    {
        public static void Main(string[] args)
        {
            using (var reader =
                   new StreamReader(@"/home/sergi/Projects/2122.icpt-p4-s1108198/csharp/csharp/cijfers.csv"))
            {
                List<Resultaat> list = new List<Resultaat>();
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');
                    Resultaat resultaat = new Resultaat()
                    {
                        Code = values[0],
                        EC = values[1],
                        Cijfer = values[2]
                    };
                    list.Add(resultaat);
                }

                // Ask user which column to sort by
                Console.WriteLine("Welk veld wil je sorteren?");
                Console.WriteLine("1. Code");
                Console.WriteLine("2. EC");
                Console.WriteLine("3. Cijfer");
                Console.Write(">> ");
                int column = Convert.ToInt32(Console.ReadLine());
                // Ask user if ascending or descending
                Console.WriteLine("Wilt u de sorteervolgorde oplopend of aflopend?");
                Console.WriteLine("1. Oplopend");
                Console.WriteLine("2. Aflopend");
                Console.Write(">> ");
                int order = Convert.ToInt32(Console.ReadLine());

                // Sort list
                list = sortFields[(column - 1) * 2 + order - 1](list);

                foreach (var resultaat in list)
                {
                    Console.WriteLine(resultaat.Code + "\t" + resultaat.EC + "\t" + resultaat.Cijfer);
                }
            }
        }

        static Func<List<Resultaat>, List<Resultaat>>[] sortFields =
        {
            (list) =>
            {
                list.Sort((x, y) => x.Code.CompareTo(y.Code));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) => y.Code.CompareTo(x.Code));
                return list;
            },

            (list) =>
            {
                list.Sort((x, y) => x.EC.CompareTo(y.EC));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) => y.EC.CompareTo(x.EC));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) => x.NepCijfer.CompareTo(y.NepCijfer));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) => y.NepCijfer.CompareTo(x.NepCijfer));
                return list;
            },
        };
    }
}