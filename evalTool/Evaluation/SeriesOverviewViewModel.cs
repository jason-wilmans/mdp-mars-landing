using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows.Forms;
using OxyPlot;

namespace Evaluation
{
    class SeriesOverviewViewModel : INotifyPropertyChanged
    {
        private static string ResultFolderPath;
        private string OutputFolder;

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

        public IList<TestSeries> CurrenSeriesList => new[] {CurrentSeries};

        public TestSeries CurrentSeries
        {
            get { return _currentSeries; }
            set
            {
                _currentSeries = value;
                NotifyPropertyChanged();
                NotifyPropertyChanged(nameof(CurrenSeriesList));
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

        public PlotModel MultiTrajectory
        {
            get { return _multiTrajectory; }
            set
            {
                _multiTrajectory = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel SpeedHeightModel
        {
            get { return _speedHeightModel; }
            set
            {
                _speedHeightModel = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel DensityModel
        {
            get { return _densityModel; }
            set
            {
                _densityModel = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel AtmosphereModel { get; set; }

        public PlotModel MachSpeedModel
        {
            get { return _machSpeedModel; }
            set
            {
                _machSpeedModel = value;
                NotifyPropertyChanged();
            }
        }

        public PlotModel GModel
        {
            get { return _gModel; }
            set
            {
                _gModel = value;
                NotifyPropertyChanged();
            }
        }

        public double MinG { get; set; }

        public double MaxG { get; set; }

        private readonly SeriesParser _seriesParser;
        private double _selectedLd;
        private double _selectedAngle;
        private int _selectedSpeed;
        private TestSeries _currentSeries;
        private PlotModel _trajectoryModel;
        private readonly DiagramService _diamgramService;
        private readonly OutputService _outputService;
        private PlotModel _accelerationModel;
        private PlotModel _speedHeightModel;
        private PlotModel _densityModel;
        private PlotModel _machSpeedModel;
        private PlotModel _gModel;
        private PlotModel _multiTrajectory;


        public SeriesOverviewViewModel()
        {
            if (App.Current.MainWindow != null)
            {
                DetermineFolders();

                _diamgramService = new DiagramService();
                _seriesParser = new SeriesParser();
                var readSeries = UpdateSeries();

                MinG = readSeries.Min(s => s.MaxAccleration);
                MaxG = readSeries.Max(s => s.MaxAccleration);

                AtmosphereModel = _diamgramService.PrepareAtmosphereDiagram(0.1921);

                _selectedLd = readSeries[0].LiftToDragCoefficient;
                _selectedAngle = readSeries[0].EntryAngle;
                _selectedSpeed = readSeries[0].EntrySpeed;
                UpdateSelectedSeries();
                UpdateAccelerationGraph();

                AvailableLDRatios = new ObservableCollection<double>(readSeries.Select(s => s.LiftToDragCoefficient).Distinct().ToList());
                AvailableAngles = new ObservableCollection<double>(readSeries.Select(s => s.EntryAngle).Distinct().ToList());
                AvailableSpeeds = new ObservableCollection<int>(readSeries.Select(s => s.EntrySpeed).Distinct().ToList());

                _outputService = new OutputService(OutputFolder, _diamgramService);
                _outputService.WriteAcclerationGraphs(TestSeries);
                _outputService.WriteTrajectoriesGraphs(TestSeries);
            }
        }

        private void DetermineFolders()
        {
            var dialog = new FolderBrowserDialog
            {
                SelectedPath = Application.StartupPath
            };

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                ResultFolderPath = dialog.SelectedPath + "\\";
                OutputFolder = ResultFolderPath + "evaluated\\";
            }
            else
            {
                App.Current.MainWindow.Close();
            }
        }

        private void UpdateModels()
        {
            TrajectoryModel = _diamgramService.PrepareTrajectoryDiagram(CurrentSeries);
            SpeedHeightModel = _diamgramService.PrepareSpeedHeightDiagram(CurrentSeries);
            MultiTrajectory = _diamgramService.PrepareTrajectoriesGraph(SelectedLD, TestSeries);
            if(CurrentSeries.Density != null) DensityModel = _diamgramService.PrepareDensityChart(CurrentSeries);
            if (CurrentSeries.MachSpeed != null) MachSpeedModel = _diamgramService.PrepareMachSpeedChart(CurrentSeries);
            if (CurrentSeries.Acceleration != null) GModel = _diamgramService.PrepareGChart(CurrentSeries);
        }

        protected virtual void NotifyPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void UpdateSelectedSeries()
        {
            double delta = 0.00001;
            var series =
                TestSeries.SingleOrDefault(
                    s =>
                        Math.Abs(s.LiftToDragCoefficient - SelectedLD) < delta && Math.Abs(s.EntryAngle - SelectedAngle) < delta &&
                        s.EntrySpeed == SelectedSpeed);
            if (series != null)
            {
                CurrentSeries = series;
            }

            UpdateModels();
        }
        private IList<TestSeries> UpdateSeries()
        {
            var readSeries = _seriesParser.ReadSeries(ResultFolderPath + "raw");
            TestSeries = new ObservableCollection<TestSeries>(readSeries);
            return readSeries;
        }

        public void OutputDiagramsForCurrentSeries()
        {
            string seriesFolder = _outputService.EnsureFolderExists(CurrentSeries);
            _outputService.WritePdf(TrajectoryModel, seriesFolder + "trajectory");
            _outputService.WritePdf(SpeedHeightModel, seriesFolder + "speedToHeight");
            _outputService.WritePdf(DensityModel, seriesFolder + "density");
            _outputService.WritePdf(MachSpeedModel, seriesFolder + "mach");
            _outputService.WritePdf(GModel, seriesFolder + "g");
        }
    }
}
