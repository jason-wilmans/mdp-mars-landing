using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace Evaluation
{
    class SeriesParser
    {
        public IList<TestSeries> ReadSeries(string dataFolderPath)
        {
            var seriesFolder = FindAllSeries(dataFolderPath);

            var parsed = new List<TestSeries>();
            foreach (var series in seriesFolder)
            {
                try
                {
                    parsed.Add(ParseSeriesFolder(series));
                }
                catch (Exception)
                {
                    break;
                }
            }

            return parsed;
        }

        private TestSeries ParseSeriesFolder(string seriesPath)
        {
            string[] parts = seriesPath.Split('\\');
            double ldRatio = double.Parse(parts[parts.Length - 3], CultureInfo.InvariantCulture);
            double angle = double.Parse(parts[parts.Length - 2], CultureInfo.InvariantCulture);
            int speed = int.Parse(parts[parts.Length - 1], CultureInfo.InvariantCulture);

            TestSeries series = new TestSeries(ldRatio, angle, speed, 0.5);
            series.Acceleration = ParseData(seriesPath + "\\" + "acceleration.out");
            series.AirSpeed = ParseData(seriesPath + "\\" + "airSpeed.out");
            series.Speed = ParseData(seriesPath + "\\" + "speed.out", true);
            series.Position = ParseData(seriesPath + "\\" + "position.out", true);

            return series;
        }

        private DataSeries ParseData(string dataFile, bool isVector = false)
        {
            DataSeries data = new DataSeries(isVector);
            using (var stream = new StreamReader(dataFile))
            {
                
                while (!stream.EndOfStream)
                {
                    string line = stream.ReadLine();
                    if (!string.IsNullOrWhiteSpace(line))
                    {
                        double d = double.Parse(line.Trim(), CultureInfo.InvariantCulture);
                        data.Add(d);
                    }
                }
            }

            if(isVector && data.Count % 2 != 0) throw new FileFormatException(new Uri(dataFile));
            return data;
        }

        private IList<string> FindAllSeries(string path)
        {
            IList<string> series = new List<string>();

            foreach (var liftFolder in Directory.EnumerateDirectories(path))
            {
                foreach (var angleFolder in Directory.EnumerateDirectories(liftFolder))
                {
                    foreach (var speedFolder in Directory.EnumerateDirectories(angleFolder))
                    {
                        series.Add(speedFolder);
                    }
                }
            }

            return series;
        }
    }
}