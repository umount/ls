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

class ListDir {
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

class Ls {
public:
    map<int, string> StructDir;
    /*
     * Create struct for print
     * Mode | UID | GID | Size | Modify | Time  | Name
     *
     */
    create_struct(vector<string> lsdir) {
        for (int i=0; i<lsdir.size(); i++) {
            dirnow = new char[lsdir[i].length() + 1];
            strcpy(dirnow, lsdir[i].c_str());

            char time[25];
            stat(dirnow,&objFile);
            struct tm * timeinfo;

            timeinfo = localtime(&objFile.st_ctime);
            strftime(time,sizeof(time),"%Y-%m-%d %H:%M",timeinfo);

            //sprintf(s_format, "\%%ds", width);

        }
    }
};

int main() {
    vector<string> lsdir;

    struct stat objFile;
    char * dirnow;

    ListDir l;
    lsdir = l.createlist();

    printf("Mode\tUID\tGID\tSize\t\tModify Time\tName\n");

//    for (int i=0; i<lsdir.size(); i++) {
//        dirnow = new char[lsdir[i].length() + 1];
//        strcpy(dirnow, lsdir[i].c_str());
//
//        char time[25];
//        stat(dirnow,&objFile);
//        struct tm * timeinfo;
//
//        timeinfo = localtime(&objFile.st_ctime);
//        strftime(time,sizeof(time),"%Y-%m-%d %H:%M",timeinfo);
//
//        printf("%lo \t", (unsigned long)objFile.st_mode);
//        printf("%d \t ", objFile.st_uid);
//        printf("%d \t ", objFile.st_gid);
//        printf("%d \t\t", (int)objFile.st_size);
//        printf("%s \t", time);
//        printf("%s \n", dirnow);
//
//    }
}
