using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using OxyPlot;

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

        public void WriteAcclerationGraphs(IList<TestSeries> testSeries)
        {
            var path = _outputFolder;
            if (Directory.Exists(path))
            {
                Directory.Delete(path, true);
            }

            Directory.CreateDirectory(path);
            
            foreach (var ld in testSeries.Select(s => s.LiftToDragCoefficient).Distinct())
            {
                OutputAccelerationGraphFor(ld, testSeries);
            }
        }

        private void OutputAccelerationGraphFor(double ld, IList<TestSeries> testSeries)
        {
            var ldFolderPath = GetLdFolderPath(ld);
            EnsureFolderExists(ldFolderPath);
            var model = _diagramService.PrepareAccelerationGraphFor(ld, testSeries);
            
            WritePdf(model, ldFolderPath + "acceleration.pdf");
        }


        private void OutputTrajectory(TestSeries series, string seriesPath)
        {
            var model = _diagramService.PrepareTrajectoryDiagram(series);

            WritePdf(model, seriesPath + "trajectory.pdf");
        }



        private string EnsureFolderExists(TestSeries testSeries)
        {
            string folder = GetLdFolderPath(testSeries.LiftToDragCoefficient);
            EnsureFolderExists(folder);

            folder += testSeries.EntryAngle.ToString(CultureInfo.InvariantCulture) + "\\";
            EnsureFolderExists(folder);

            folder += testSeries.EntrySpeed + "\\";
            EnsureFolderExists(folder);

            return folder;
        }

        private void EnsureFolderExists(string path)
        {
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }
        }

        private string GetLdFolderPath(double ld)
        {
            return _outputFolder + ld.ToString("F2") + "\\";
        }
        
        public void WritePdf(PlotModel model, string fileName)
        {
            using (var stream = File.Create(fileName + ".pdf"))
            {
                var pdfExporter = new PdfExporter { Width = 700, Height = 400 };
                pdfExporter.Export(model, stream);
            }
        }
    }
}