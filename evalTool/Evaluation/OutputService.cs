using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using OxyPlot;
using OxyPlot.Series;

namespace Evaluation
{
    class OutputService
    {
        private readonly string _outputFolder;
        private readonly DiagramService _diagramService;

        public OutputService(string outputFolder, DiagramService _diagramService)
        {
            _outputFolder = outputFolder;
            this._diagramService = _diagramService;
        }

        public void WriteEvaulationData(IList<TestSeries> testSeries)
        {
            var path = _outputFolder;
            if (Directory.Exists(path))
            {
                Directory.Delete(path, true);
            }

            Directory.CreateDirectory(path);

            foreach (var series in testSeries)
            {
                string seriesPath = EnsurePathExists(series);
                OutputTrajectory(series, seriesPath);
            }

            foreach (var ld in testSeries.Select(s => s.LiftToDragCoefficient).Distinct())
            {
                OutputAccelerationGraphFor(ld, testSeries);
            }
        }

        private void OutputAccelerationGraphFor(double ld, IList<TestSeries> testSeries)
        {
            var model = _diagramService.PrepareAccelerationGraphFor(ld, testSeries);

            using (var stream = File.Create(GetLdFolderPath(ld) + "acceleration.pdf"))
            {
                var pdfExporter = new PdfExporter { Width = 700, Height = 400 };
                pdfExporter.Export(model, stream);
            }
        }


        private void OutputTrajectory(TestSeries series, string seriesPath)
        {
            var model = _diagramService.PrepareTrajectoryDiagram(series);

            using (var stream = File.Create(seriesPath + "trajectory.pdf"))
            {
                var pdfExporter = new PdfExporter {Width = 700, Height = 400};
                pdfExporter.Export(model, stream);
            }
        }

        private string EnsurePathExists(TestSeries testSeries)
        {
            string folder = GetLdFolderPath(testSeries.LiftToDragCoefficient);
            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }

            folder += testSeries.EntryAngle.ToString(CultureInfo.InvariantCulture) + "\\";

            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }

            folder += testSeries.EntrySpeed + "\\";
            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }

            return folder;
        }

        private string GetLdFolderPath(double testSeries)
        {
            return _outputFolder + testSeries.ToString(CultureInfo.InvariantCulture) + "\\";
        }
    }
}