// // <copyright file="DiagramService.cs" year="2016" owner="Fritz Oscar S. Berngruber & Jason Wilmans" email="fw.project@gmx.de">
// // All rights are reserved. Reproduction or transmission in whole or in part, in
// // any form or by any means, electronic, mechanical or otherwise, is prohibited
// // without the prior written consent of the copyright owner.
// // </copyright>

using System;
using System.Collections.Generic;
using System.Linq;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;

namespace Evaluation
{
    class DiagramService
    {
        public PlotModel PrepareSpeedHeightDiagram(TestSeries testSeries)
        {
            var bottom = new LinearAxis { Position = AxisPosition.Bottom, Title = "Geschwindigkeit (km/s)", Minimum = 0, Maximum = 8.0 };
            var left = new LinearAxis { Position = AxisPosition.Left, Title = "Höhe (km)", Minimum = 0, Maximum = 150 };
            var xAxis = testSeries.AirSpeed.EnumerateAll().Select(s => s / 1000);
            var yAxis = testSeries.Position.EnumerateEven().Select(s => s / 1000);
            var dataPoints = CreateDataPoints(xAxis, yAxis);
            return PrepareLineChart("Höhe/Geschwindigkeit", dataPoints, bottom, left, OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff));
        }

        public PlotModel PrepareTrajectoryDiagram(TestSeries testSeries)
        {
            var bottom = new LinearAxis { Position = AxisPosition.Bottom, Title = "Horizontale Distanz (km)", Minimum = 0, Maximum = 1000 };
            var left = new LinearAxis { Position = AxisPosition.Left, Title = "Höhe (km)", Minimum = 0, Maximum = 125 };
            var xAxis = testSeries.Position.EnumerateOdd().Select(s => s / 1000);
            var yAxis = testSeries.Position.EnumerateEven().Select(s => s / 1000);
            var dataPoints = CreateDataPoints(xAxis, yAxis);
            return PrepareLineChart("Trajektor", dataPoints, bottom, left, OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff));
        }

        public PlotModel PrepareDensityChart(TestSeries testSeries)
        {
            var bottom = new LinearAxis { Position = AxisPosition.Bottom, Title = "Zeit (s)", Minimum = 0, Maximum = testSeries.LastTimeStamp };
            var left = new LinearAxis { Position = AxisPosition.Left, Title = "Druck (kg/m³)", Minimum = 0, Maximum = 0.02 };
            var xAxis = testSeries.EnumerateTimeValues();
            var yAxis = testSeries.Density.EnumerateAll();
            var dataPoints = CreateDataPoints(xAxis, yAxis);
            return PrepareLineChart("Atmosphärendruck", dataPoints, bottom, left, OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff));
        }
        public PlotModel PrepareMachSpeedChart(TestSeries testSeries)
        {
            var bottom = new LinearAxis { Position = AxisPosition.Bottom, Title = "Zeit (s)", Minimum = 0, Maximum = testSeries.LastTimeStamp };
            var left = new LinearAxis { Position = AxisPosition.Left, Title = "Geschwindigkeit (Mach)", Minimum = 0, Maximum = 275 };
            var xAxis = testSeries.EnumerateTimeValues();
            var yAxis = testSeries.MachSpeed.EnumerateAll();
            var dataPoints = CreateDataPoints(xAxis, yAxis);
            return PrepareLineChart("Atmosphärendruck", dataPoints, bottom, left, OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff));
        }

        public PlotModel PrepareGChart(TestSeries testSeries)
        {
            var bottom = new LinearAxis { Position = AxisPosition.Bottom, Title = "Zeit (s)", Minimum = 0, Maximum = testSeries.LastTimeStamp };
            var left = new LinearAxis { Position = AxisPosition.Left, Title = "Beschleunigung (g)", Minimum = 0, Maximum = 70 };
            var xAxis = testSeries.EnumerateTimeValues();
            var yAxis = testSeries.Acceleration.EnumerateAll();
            var dataPoints = CreateDataPoints(xAxis, yAxis);
            return PrepareLineChart("Atmosphärendruck", dataPoints, bottom, left, OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff));
        }

        public PlotModel PrepareTrajectoriesGraph(double ld, IList<TestSeries> testSeries)
        {
            var minColor = OxyColor.FromArgb(0xff, 0x00, 0xdb, 0xff);
            var maxColor = OxyColor.FromArgb(0xff, 0xff, 0x72, 0x00);
            
            IList<Line> lines = new List<Line>();
            foreach (var series in testSeries.Where(s => s.LiftToDragCoefficient == ld))
            {
                var xAxis = series.Position.EnumerateOdd().Select(s => s / 1000);
                var yAxis = series.Position.EnumerateEven().Select(s => s / 1000);
                var dataPoints = CreateDataPoints(xAxis, yAxis);
                var color = Math.Abs(series.EntryAngle - 15.0) < 0.1 && series.EntrySpeed == 6000 ? maxColor : minColor;
                lines.Add(new Line(dataPoints, color));
            }

            var bottom = new LinearAxis { Position = AxisPosition.Bottom, Title = "Horizontale Distanz (km)", Minimum = 0, Maximum = 1000 };
            var left = new LinearAxis { Position = AxisPosition.Left, Title = "Höhe (km)", Minimum = 0, Maximum = 125 };
            return PrepareMultiLineChart("Trajektorien nach L/D", bottom, left, lines);
        }

        private List<DataPoint> CreateDataPoints(
            IEnumerable<double> xAxis,
            IEnumerable<double> yAxis, double xFactor = 1.0, double yFactor = 1.0)
        {
            List<DataPoint> points = new List<DataPoint>();
            IEnumerator<double> xValues = xAxis.GetEnumerator();
            IEnumerator<double> yValues = yAxis.GetEnumerator();

            while (xValues.MoveNext() && yValues.MoveNext())
            {
                points.Add(new DataPoint(xValues.Current*xFactor, yValues.Current*yFactor));
            }

            return points;
        }

        public PlotModel PrepareAccelerationGraphFor(double ld, IList<TestSeries> testSeries)
        {
            var m = new PlotModel
            {
                Title = "Maximale Beschleunigung",
                Axes =
                {
                    new LinearAxis {Position = AxisPosition.Left, Title = "Geschwindigkeit (m/s)", Minimum = testSeries.Min(s => s.EntrySpeed), Maximum = testSeries.Max(s => s.EntrySpeed)},
                    new LinearAxis {Position = AxisPosition.Bottom, Title = "Eintrittswinkel (°)", Minimum = testSeries.Min(s => -s.EntryAngle), Maximum = testSeries.Max(s => -s.EntryAngle)}
                }
            };
            var angles = testSeries.Where(s => s.LiftToDragCoefficient == ld).Select(s => -s.EntryAngle).Distinct().ToArray();
            var speeds = testSeries.Where(s => s.LiftToDragCoefficient == ld).Select(s => (double)s.EntrySpeed).Distinct().ToArray();
            var max = testSeries.Max(s => s.MaxAccleration);
            var accelerationTable = CalculateAccelerationTable(ld, angles, speeds, testSeries);
            var minColor = OxyColor.FromArgb(0xff, 0x00, 0xdb, 0xff);
            var maxColor = OxyColor.FromArgb(0xff, 0xff, 0x72, 0x00);
            var contours = GenerateContours(0.0, max, minColor, maxColor, 30);
            var cs = new ContourSeries
            {
                ColumnCoordinates = angles,
                RowCoordinates = speeds,
                Data = accelerationTable,
                ContourLevels = contours.Select(c => c.Limit).ToArray(),
                ContourColors = contours.Select(c => c.Color).ToArray(),
                LabelFormatString = "F1",
                RenderInLegend = true
            };
            
            cs.CalculateContours();
            m.Series.Add(cs);
            return m;
        }

        private Contour[] GenerateContours(double min, double max, OxyColor minColor, OxyColor maxColor, int nrOfContours)
        {
            double delta = max - min;
            double stepSize = delta / nrOfContours;
            double colorStepSize = 1/(double)nrOfContours;
            var contours = new Contour[nrOfContours];
            for (int i = 1; i <= nrOfContours; i++)
            {
                contours[i - 1] = new Contour(min + i * stepSize, OxyColor.Interpolate(minColor, maxColor, i * colorStepSize));
            }
            return contours;
        }

        private double[,] CalculateAccelerationTable(double ld, double[] angles, double[] speeds, IEnumerable<TestSeries> testSeries)
        {
            double[,] table = new double[angles.Length, speeds.Length];

            for (int angle = 0; angle < angles.Length; angle++)
            {
                for (int speed = 0; speed < speeds.Length; speed++)
                {
                    table[angle, speed] =
                        testSeries.Where(
                            s =>
                                s.LiftToDragCoefficient == ld && s.EntryAngle == -angles[angle] &&
                                s.EntrySpeed == speeds[speed]).Select(s => s.MaxAccleration).Single();
                }
            }

            return table;
        }

        public PlotModel PrepareAtmosphereDiagram(double R)
        {
            // Create the plot model
            var model = new PlotModel
            {
                Title = "Dichte",
                Axes =
                {
                    new LinearAxis {Position = AxisPosition.Bottom, Title = "Height (m)", Minimum = 0, Maximum = 125000},
                    new LinearAxis {Position = AxisPosition.Left, Title = "Dichte (kg/m³)", Minimum = 0.0, Maximum = 0.015}
                }
            };

            var series1 = new LineSeries
            {
                Color = OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff),
                StrokeThickness = 1.0,
                LineStyle = LineStyle.Solid
            };

            IList<DataPoint> points = PlotFunction(125000, 10, R);
            series1.Points.AddRange(points);

            model.Series.Add(series1);
            return model;
        }

        private IList<DataPoint> PlotFunction(double maxValue, double stepSize, double R)
        {
            IList<DataPoint> points = new List<DataPoint>();
            double x = 0;
            while (x <= maxValue)
            {
                points.Add(new DataPoint(x, AthmosphereModel(x, R)));
                x += stepSize;
            }

            return points;
        }

        private double AthmosphereModel(double height, double R)
        {
            var p = 0.699 * Math.Exp(-0.00009 * height);
            double T;
            if (height > 7000)
            {
                T = -23.4 - 0.00222 * height;
            }
            else
            {
                T = -31 - 0.000998 * height;
            }

            return p / (R * (T + 273.1));
        }

        public PlotModel PrepareMultiLineChart(string title, Axis bottom, Axis left, IEnumerable<Line> lines)
        {
            var model = new PlotModel
            {
                Title = title,
                Axes =
                {
                    bottom,
                    left
                }
            };

            foreach (var line in lines)
            {
                var series = new LineSeries
                {
                    Color = line.Color,
                    StrokeThickness = 1.0,
                    LineStyle = LineStyle.Solid,
                    MarkerType = MarkerType.Circle
                };

                series.Points.AddRange(line.Points);

                model.Series.Add(series);
            }
            
            return model;
        }

    public PlotModel PrepareLineChart(string title, List<DataPoint> points, Axis bottom, Axis left, OxyColor lineColor)
        {
            var model = new PlotModel
            {
                Title = title,
                Axes =
                {
                    bottom,
                    left
                }
            };

            var series1 = new LineSeries
            {
                Color = lineColor,
                StrokeThickness = 1.0,
                LineStyle = LineStyle.Solid,
                MarkerType = MarkerType.Circle
            };

            series1.Points.AddRange(points);

            model.Series.Add(series1);
            return model;
        }
    }

    internal struct Contour
    {
        public double Limit;
        public OxyColor Color;

        public Contour(double limit, OxyColor color)
        {
            Limit = limit;
            Color = color;
        }
    }

    internal struct Line
    {
        public IList<DataPoint> Points;
        public OxyColor Color;

        public Line(IList<DataPoint> points, OxyColor color)
        {
            Points = points;
            Color = color;
        }
    }
}