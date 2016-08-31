using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

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
            series.MachSpeed = ParseData(seriesPath + "\\" + "machSpeed.out");
            series.Speed = ParseData(seriesPath + "\\" + "speed.out", true);
            series.AirSpeed = ParseData(seriesPath + "\\" + "airSpeed.out");
            series.Position = ParseData(seriesPath + "\\" + "position.out", true);
            series.Acceleration = ParseData(seriesPath + "\\" + "acceleration.out");
            series.Density = ParseData(seriesPath + "\\" + "density.out");
            series.Throttle = ParseData(seriesPath + "\\" + "throttle.out");
            series.Thrust = ParseData(seriesPath + "\\" + "thrust.out");
            series.Fuel = ParseData(seriesPath + "\\" + "fuel.out");

            return series;
        }

        private DataSeries ParseData(string dataFile, bool isVector = false)
        {
            if (!File.Exists(dataFile)) return null;
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