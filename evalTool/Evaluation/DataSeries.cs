using System.Collections;
using System.Collections.Generic;

namespace Evaluation
{
    class DataSeries
    {
        private readonly IList<double> _values;
        public bool IsVector { get; }
        public int Count => _values.Count;

        public DataSeries(bool isVector)
        {
            IsVector = isVector;
            _values = new List<double>();
        }

        public void Add(double value)
        {
            _values.Add(value);
        }

        public IEnumerable<double> EnumerateAll()
        {
            return _values;
        }

        public IEnumerable<double> EnumerateEven()
        {
            return new SkipEnumerable(_values.GetEnumerator(), false);
        }

        public IEnumerable<double> EnumerateOdd()
        {
            return new SkipEnumerable(_values.GetEnumerator(), true);
        }
    }

    internal class SkipEnumerable : IEnumerable<double>, IEnumerator<double>
    {
        private readonly IEnumerator<double> _original;
        private readonly bool _odd;

        public SkipEnumerable(IEnumerator<double> original, bool odd)
        {
            _original = original;
            _odd = odd;
            SkipIfOdd();
        }

        private void SkipIfOdd()
        {
            if (_odd)
            {
                _original.MoveNext();
            }
        }

        public void Dispose() { _original.Dispose(); }

        public bool MoveNext()
        {
            _original.MoveNext();
            return _original.MoveNext();
        }

        public void Reset()
        {
            _original.Reset();
            SkipIfOdd();
        }

        public double Current => _original.Current;

        object IEnumerator.Current => _original.Current;
        public IEnumerator<double> GetEnumerator()
        {
            return this;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
