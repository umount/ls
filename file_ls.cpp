/*
 * Форматитрование текта и вывода команды ls
 * @author Denis Sobolev <dns.sobol@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

class Controller {
public:
    vector<string> createlist() {
        vector<string> lsdir;
        DIR *curDir = NULL;
        struct dirent *objDir;

        curDir = opendir(get_current_dir_name());
        while((objDir=readdir(curDir))!=NULL) {
            char * base_name = objDir->d_name;
            lsdir.push_back(base_name);
        }
        sort(lsdir.begin(), lsdir.end());
        closedir(curDir);
        return lsdir;
    };
};

class Model {
public:
    vector< vector<string> > StructDir;

    /*
     * Create struct for print
     * Mode | UID | GID | Size | Modify time  | Name
     *
     */
    void create_struct(vector<string> lsdir) {
        struct stat objFile;
        char * dirnow;
        char mode[10],uid[5],gid[5],size[100];
        for (int i=0; i<lsdir.size(); i++) {
            vector<string> line;
            dirnow = new char[lsdir[i].length() + 1];
            strcpy(dirnow, lsdir[i].c_str());

            char time[25];
            stat(dirnow,&objFile);
            struct tm * timeinfo;

            timeinfo = localtime(&objFile.st_ctime);
            strftime(time,sizeof(time),"%Y-%m-%d %H:%M",timeinfo);

            sprintf(mode, "%lo", (unsigned long)objFile.st_mode);
            sprintf(uid, "%d", objFile.st_uid);
            sprintf(gid, "%d", objFile.st_gid);
            sprintf(size, "%d", (int)objFile.st_size);

            line.push_back(mode);
            line.push_back(uid);
            line.push_back(gid);
            line.push_back(size);
            line.push_back(time);
            line.push_back(dirnow);

            StructDir.push_back(line);
        }
    };
};


class View {
public:
    void Print(vector< vector<string> > dir_struct){
        for (int i=0; i<dir_struct.size(); i++) {
            for (int j=0; j<dir_struct[i].size(); j++){
                cout << dir_struct[i][j] << endl;
                //printf("%s \t", dir_struct[i][j]);
            }
            printf("\n");
        }
    }
};

int main() {
    vector<string> lsdir;
    vector< vector<string> > dir_struct;

    Controller c;
    lsdir = c.createlist();

    Model m;
    m.create_struct(lsdir);
    dir_struct = m.StructDir;

    View v;
    v.Print(dir_struct);
}
