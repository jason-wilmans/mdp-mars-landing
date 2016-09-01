using System.Collections.Generic;
using System.Collections.ObjectModel;
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
        private string _aggregateFolder;

        public OutputService(string outputFolder, DiagramService _diagramService)
        {
            _outputFolder = outputFolder;
            _aggregateFolder = outputFolder + "aggregate\\";
            EnsureFolderExists(_aggregateFolder);
            this._diagramService = _diagramService;
        }

        public void WriteAcclerationGraphs(IList<TestSeries> testSeries)
        {
            EnsureFolderExists(_outputFolder);
            
            foreach (var ld in testSeries.Select(s => s.LiftToDragCoefficient).Distinct())
            {
                var model = _diagramService.PrepareAccelerationGraphFor(ld, testSeries);
                WritePdf(model, _aggregateFolder + $"acc{ld.ToString(CultureInfo.InvariantCulture)}");
            }
        }

        public void WriteTrajectoriesGraphs(IList<TestSeries> testSeries)
        {
            EnsureFolderExists(_outputFolder);

            foreach (var ld in testSeries.Select(s => s.LiftToDragCoefficient).Distinct())
            {
                var model = _diagramService.PrepareTrajectoriesGraph(ld, testSeries);

                WritePdf(model, _aggregateFolder + $"multiTrajec{ld.ToString(CultureInfo.InvariantCulture)}");
            }
        }

        public string EnsureFolderExists(TestSeries testSeries)
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
            var toCreate = path.Split('\\');
            string current = $"{toCreate[0]}\\";
            for (int i = 1; i < toCreate.Length; i++)
            {
                current += toCreate[i] + "\\";
                if (!Directory.Exists(current))
                {
                    Directory.CreateDirectory(current);
                }
            }
        }

        public string GetLdFolderPath(double ld)
        {
            return _outputFolder + ld.ToString("F2") + "\\";
        }
        
        public void WritePdf(PlotModel model, string fileName)
        {
            using (var stream = File.Create(fileName + ".pdf"))
            {
                var pdfExporter = new PdfExporter { Width = 700, Height = 500 };
                pdfExporter.Export(model, stream);
            }
        }
    }
}