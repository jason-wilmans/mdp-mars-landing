using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using OxyPlot;

namespace Evaluation
{
    class SeriesOverviewViewModel : INotifyPropertyChanged
    {
        private static readonly string ResultFolderPath = "..\\..\\..\\..\\results\\";
        private readonly string OutputFolder = ResultFolderPath + "evaluated\\";

        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<TestSeries> TestSeries { get; set; }
        public ObservableCollection<double> AvailableLDRatios { get; }
        public ObservableCollection<double> AvailableAngles { get; }
        public ObservableCollection<int> AvailableSpeeds { get; set; }

        public double SelectedLD
        {
            get { return _selectedLd; }
            set
            {
                _selectedLd = value;
                UpdateSelectedSeries();
                UpdateAccelerationGraph();
                NotifyPropertyChanged();
            }
        }

        private void UpdateAccelerationGraph()
        {
            AccelerationModel = _diamgramService.PrepareAccelerationGraphFor(SelectedLD, TestSeries);
        }

        public double SelectedAngle
        {
            get { return _selectedAngle; }
            set
            {
                _selectedAngle = value;
                UpdateSelectedSeries();
                NotifyPropertyChanged();
            }
        }

        public int SelectedSpeed
        {
            get { return _selectedSpeed; }
            set
            {
                _selectedSpeed = value;
                UpdateSelectedSeries();
                NotifyPropertyChanged();
            }
        }

        public ObservableCollection<TestSeries> CurrentSeries
        {
            get { return _currentSeries; }
            set
            {
                _currentSeries = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel TrajectoryModel
        {
            get { return _trajectoryModel; }
            set
            {
                _trajectoryModel = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel AccelerationModel
        {
            get { return _accelerationModel; }
            set
            {
                _accelerationModel = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel AtmosphereModel { get; set; }

        private readonly SeriesParser _seriesParser;
        private double _selectedLd;
        private double _selectedAngle;
        private int _selectedSpeed;
        private ObservableCollection<TestSeries> _currentSeries;
        private PlotModel _trajectoryModel;
        private DiagramService _diamgramService;
        private readonly OutputService _outputService;
        private PlotModel _accelerationModel;


        public SeriesOverviewViewModel()
        {
            _diamgramService = new DiagramService();
            _seriesParser = new SeriesParser();
            var readSeries = UpdateSeries();

            _selectedLd = readSeries[0].LiftToDragCoefficient;
            _selectedAngle = readSeries[0].EntryAngle;
            _selectedSpeed = readSeries[0].EntrySpeed;
            CurrentSeries = new ObservableCollection<TestSeries>();
            UpdateSelectedSeries();
            UpdateAccelerationGraph();

            AvailableLDRatios = new ObservableCollection<double>(readSeries.Select(s => s.LiftToDragCoefficient).Distinct().ToList());
            AvailableAngles = new ObservableCollection<double>(readSeries.Select(s => s.EntryAngle).Distinct().ToList());
            AvailableSpeeds = new ObservableCollection<int>(readSeries.Select(s => s.EntrySpeed).Distinct().ToList());
            _outputService = new OutputService(OutputFolder, _diamgramService);
            //_outputService.WriteEvaulationData(TestSeries);
            AtmosphereModel = _diamgramService.PrepareAtmosphereDiagram(0.1921);
            _outputService.WritePdf(AtmosphereModel, "nasa");
            AtmosphereModel = _diamgramService.PrepareAtmosphereDiagram(0.15);
            _outputService.WritePdf(AtmosphereModel, "custom");
        }

        private void UpdateModel()
        {
            TrajectoryModel = _diamgramService.PrepareTrajectoryDiagram(CurrentSeries[0]);
        }

        protected virtual void NotifyPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void UpdateSelectedSeries()
        {
            CurrentSeries.Clear();
            double delta = 0.00001;
            var series =
                TestSeries.SingleOrDefault(
                    s =>
                        Math.Abs(s.LiftToDragCoefficient - SelectedLD) < delta && Math.Abs(s.EntryAngle - SelectedAngle) < delta &&
                        s.EntrySpeed == SelectedSpeed);
            if (series != null)
            {
                CurrentSeries.Add(series);
            }


            UpdateModel();
        }
        private IList<TestSeries> UpdateSeries()
        {
            var readSeries = _seriesParser.ReadSeries(ResultFolderPath + "raw");
            TestSeries = new ObservableCollection<TestSeries>(readSeries);
            return readSeries;
        }
    }
}
