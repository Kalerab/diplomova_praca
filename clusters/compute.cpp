#include "compute.h"
#include <iostream>
#include <vector>
#include "mainprogram.h"
#include "mainwindow.h"

using namespace std;

void computeFiles(Ui::MainWindow *ui, const vector<string> files, string currentDir, bool printclusters){
    for(int i=0; i<files.size();i++){
        string path = files[i];
        string filenameWExt;
        string filename;
        string ext;
        const size_t last_slash_idx = path.find_last_of("\\/");
        if (string::npos != last_slash_idx)
        {
            filenameWExt = path;
            filenameWExt.erase(0, last_slash_idx + 1);
        }
        const size_t period_idx = filenameWExt.rfind('.');
        if (string::npos != period_idx)
        {
            filename = filenameWExt;
            filename.erase(period_idx);
            ext = filenameWExt;
            ext.erase(0, period_idx+1);
        }

        QString curr = QString::number(i);
        QString size = QString::number(files.size());

        ui->outputWidget->addItem("Computing " + QString::fromStdString(filenameWExt));
        mainFunction(path, filename, filenameWExt, ext, currentDir, printclusters);
    }
}

