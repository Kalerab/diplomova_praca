#include "compute.h"
#include <iostream>
#include <vector>
#include "mainprogram.h"

using namespace std;

void computeFiles(const vector<string> files, bool permutation, bool allcycles, bool cycleperm, bool halfperm,
                  bool cycledoublecover, bool clusters, string currentDir){
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

        mainFunction(permutation, allcycles, cycleperm, halfperm, cycledoublecover, clusters, path, filename, filenameWExt, ext, currentDir);
//        cout << currentDir << endl;
//        cout << filenameWExt << endl;
//        cout << path << endl;
//        cout << ext << endl;
    }
}

