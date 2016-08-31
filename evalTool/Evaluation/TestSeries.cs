using System.Collections.Generic;
using System.Linq;

namespace Evaluation
{
    class TestSeries
    {
        public double LiftToDragCoefficient { get; }

        public double EntryAngle { get; }

        public int EntrySpeed { get; }

        public double TimeResolution { get; set; }

        public DataSeries Acceleration { get; set; }
        public DataSeries AirSpeed { get; set; }
        public DataSeries Temperature { get; set; }
        public DataSeries Position { get; set; }
        public DataSeries Speed { get; set; }
        public DataSeries MachSpeed { get; set; }
        public DataSeries Density { get; set; }
        public DataSeries Throttle { get; set; }
        public DataSeries Thrust { get; set; }
        public DataSeries Fuel { get; set; }

        public TestSeries(double liftToDragCoefficient, double entryAngle, int entrySpeed, double timeResolution)
        {
            LiftToDragCoefficient = liftToDragCoefficient;
            EntryAngle = entryAngle;
            EntrySpeed = entrySpeed;
            TimeResolution = timeResolution;
        }

        public double TotalTime => Acceleration.Count*TimeResolution;

        /// <summary>
        /// in km
        /// </summary>
        public double HorizontalDistance => LastDistance() / 1000;
        
        /// <summary>
        /// in Gs
        /// </summary>
        public double MaxAccleration => Acceleration.EnumerateAll().Max();

        /// <summary>
        /// m/s
        /// </summary>
        public double LastSpeed => AirSpeed.EnumerateAll().Last();

        /// <summary>
        /// m
        /// </summary>
        public double LastHeight => Position.EnumerateEven().Last();

        public string Turnout => CalculateTurnout();

        private string CalculateTurnout()
        {
            if (LastHeight <= 0.2)
            {
                return LastSpeed <= 1.0 ? "Landing" : "Crash";
            }

            return "Parachute";
        }

        private double LastDistance()
        {
            return Position.EnumerateOdd().Last();
        }

        public IEnumerable<double> EnumerateTimeValues()
        {
            IList<double> timeValues = new List<double>();
            for (int i = 0; i < AirSpeed.Count; i++)
            {
                timeValues.Add(i * TimeResolution);
            }
            return timeValues;
        }

        public double LastTimeStamp => TimeResolution*(AirSpeed.Count - 1);
    }
}
