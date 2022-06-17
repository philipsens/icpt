using System;
using System.Collections.Generic;
using System.IO;

namespace csharp
{
    internal class Resultaat
    {
        public string Code { get; set; }
        public string Ec { get; set; }

        public string Cijfer { get; set; }

        public string NepCijfer
        {
            get
            {
                return Cijfer.ToLower() switch
                {
                    "o" => "11",
                    "v" => "12",
                    "g" => "13",
                    _ => Cijfer
                };
            }
            set => Cijfer = value;
        }
    }

    internal static class Program
    {
        public static void Main(string[] args)
        {
            var resultaten = GetResultaten();
            var column = AskUserWhichColumnToSort();
            var order = AskUserAscendingDescending();

            resultaten = SortFields(resultaten, column, order);

            ShowResultaten(resultaten);
        }

        private static List<Resultaat> SortFields(List<Resultaat> resultaten, int column, int order)
        {
            var functionIndex = (column - 1) * 2 + order - 1;
            return SortFieldsFunctions[functionIndex](resultaten);
        }

        private static void ShowResultaten(List<Resultaat> resultaten)
        {
            foreach (var resultaat in resultaten)
            {
                Console.WriteLine($"{resultaat.Code}\t{resultaat.Ec}\t{resultaat.Cijfer}");
            }
        }

        private static int AskUserAscendingDescending()
        {
            Console.WriteLine("Wilt u de sorteervolgorde oplopend of aflopend?");
            Console.WriteLine("1. Oplopend");
            Console.WriteLine("2. Aflopend");
            Console.Write(">> ");
            return Convert.ToInt32(Console.ReadLine());
        }

        private static int AskUserWhichColumnToSort()
        {
            Console.WriteLine("Welk veld wil je sorteren?");
            Console.WriteLine("1. Code");
            Console.WriteLine("2. EC");
            Console.WriteLine("3. Cijfer");
            Console.Write(">> ");
            return Convert.ToInt32(Console.ReadLine());
        }

        private static List<Resultaat> GetResultaten()
        {
            var resultaten = new List<Resultaat>();
            using var reader =
                new StreamReader(@"/home/sergi/Projects/2122.icpt-p4-s1108198/csharp/csharp/cijfers.csv");
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                if (line == null) continue;
                var values = line.Split(',');
                var resultaat = new Resultaat()
                {
                    Code = values[0],
                    Ec = values[1],
                    Cijfer = values[2]
                };
                resultaten.Add(resultaat);
            }

            return resultaten;
        }

        private static readonly Func<List<Resultaat>, List<Resultaat>>[] SortFieldsFunctions =
        {
            (list) =>
            {
                list.Sort((x, y) =>
                    string.Compare(x.Code, y.Code, StringComparison.Ordinal));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) =>
                    string.Compare(y.Code, x.Code, StringComparison.Ordinal));
                return list;
            },

            (list) =>
            {
                list.Sort((x, y) =>
                    string.Compare(x.Ec, y.Ec, StringComparison.Ordinal));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) =>
                    string.Compare(y.Ec, x.Ec, StringComparison.Ordinal));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) =>
                    string.Compare(x.NepCijfer, y.NepCijfer, StringComparison.Ordinal));
                return list;
            },
            (list) =>
            {
                list.Sort((x, y) =>
                    string.Compare(y.NepCijfer, x.NepCijfer, StringComparison.Ordinal));
                return list;
            },
        };
    }
}