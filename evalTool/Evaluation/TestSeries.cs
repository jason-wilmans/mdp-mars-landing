using System.Collections.Generic;

namespace Evaluation
{
    class TestSeries<T>
    {
        public double LiftToDragCoefficient { get; }

        public double EntryAngle { get; }

        public int EntrySpeed { get; }

        public double TimeResolution { get; set; }

        private IList<T> _data;

        public TestSeries(double liftToDragCoefficient, double entryAngle, int entrySpeed, double timeResolution)
        {
            LiftToDragCoefficient = liftToDragCoefficient;
            EntryAngle = entryAngle;
            EntrySpeed = entrySpeed;
            TimeResolution = timeResolution;
        }

        public void AddDataPoint(T point)
        {
            _data.Add(point);
        }
    }
}
