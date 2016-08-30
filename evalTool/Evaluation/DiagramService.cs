﻿// // <copyright file="DiagramService.cs" year="2016" owner="Fritz Oscar S. Berngruber & Jason Wilmans" email="fw.project@gmx.de">
// // All rights are reserved. Reproduction or transmission in whole or in part, in
// // any form or by any means, electronic, mechanical or otherwise, is prohibited
// // without the prior written consent of the copyright owner.
// // </copyright>

using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;

namespace Evaluation
{
    class DiagramService
    {
        public PlotModel PrepareTrajectoryDiagram(TestSeries testSeries)
        {
            // Create the plot model
            var model = new PlotModel
            {
                Title = "Trajectory",
                Axes =
                {
                    new LinearAxis {Position = AxisPosition.Left, Title = "Height (km)", Minimum = 0, Maximum = 125},
                    new LinearAxis {Position = AxisPosition.Bottom, Title = "Distance (km)", Minimum = 0, Maximum = 1000}
                }
            };

            var series1 = new LineSeries
            {
                StrokeThickness = 0.5,
                MarkerStrokeThickness = 1.0,
                LineStyle = LineStyle.None,
                MarkerType = MarkerType.Circle
            };

            List<DataPoint> points = CreateDataPoints(
                testSeries.Position.EnumerateOdd(),
                testSeries.Position.EnumerateEven(), 0.001, 0.001
                );
            series1.Points.AddRange(points);


            model.Series.Add(series1);
            return model;
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
                    new LinearAxis {Position = AxisPosition.Left, Title = "Speed (m/s)", Minimum = 4000, Maximum = 9000},
                    new LinearAxis {Position = AxisPosition.Bottom, Title = "Angle (°)", Minimum = 10, Maximum = 20}
                }
            };
            var angles = testSeries.Where(s => s.LiftToDragCoefficient == ld).Select(s => -s.EntryAngle).Distinct().ToArray();
            var speeds = testSeries.Where(s => s.LiftToDragCoefficient == ld).Select(s => (double)s.EntrySpeed).Distinct().ToArray();
            var max = testSeries.Where(s => s.LiftToDragCoefficient == ld).Max(s => s.MaxAccleration);
            var accelerationTable = CalculateAccelerationTable(ld, angles, speeds, testSeries);
            var minColor = OxyColor.FromArgb(0xff, 0xff, 0xff, 0xff);
            var maxColor = OxyColor.FromArgb(0xff, 0xff, 0x00, 0x00);
            var contours = GenerateContours(0.0, max, minColor, maxColor, 20);
            var cs = new ContourSeries
            {
                ColumnCoordinates = angles,
                RowCoordinates = speeds,
                Data = accelerationTable,
                ContourLevels = contours.Select(c => c.Limit).ToArray(),
                ContourColors = contours.Select(c => c.Color).ToArray(),
                LabelFormatString = "F1"
                
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
                    new LinearAxis {Position = AxisPosition.Left, Title = "Dichte (kg/m³)", Minimum = -0.01, Maximum = 0.02}
                }
            };

            var series1 = new LineSeries
            {
                Color = OxyColor.FromArgb(0xff, 0x00, 0x70, 0xff),
                StrokeThickness = 0.5,
                MarkerStrokeThickness = 1.0,
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

            //return p/(0.1921 *(T + 273.1) );
            return p / (R * (T + 273.1));
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
}