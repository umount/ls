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
    void createlist(vector<string> &lsdir) {
        DIR *curDir = NULL;
        struct dirent *objDir;

        curDir = opendir(get_current_dir_name());
        while((objDir=readdir(curDir))!=NULL) {
            char * base_name = objDir->d_name;
            lsdir.push_back(base_name);
        }
        sort(lsdir.begin(), lsdir.end());
        closedir(curDir);
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
    void create_struct(vector<string> &lsdir) {
        struct stat objFile;
        char * dirnow;
        char mode[10],uid[5],gid[5],size[100];
        vector<string> head;

        head.push_back("Mode");
        head.push_back("UID");
        head.push_back("GID");
        head.push_back("Size");
        head.push_back("Modify time");
        head.push_back("Name");

        StructDir.push_back(head);

        for (int i=0; i<lsdir.size(); i++) {
            vector<string> line;
            dirnow = new char[lsdir[i].length() + 1];
            strcpy(dirnow, lsdir[i].c_str());

            char time[25];
            stat(dirnow,&objFile);
            struct tm * timeinfo;

            timeinfo = localtime(&objFile.st_ctime);
            strftime(time,sizeof(time),"%Y-%m-%d %H:%M",timeinfo);

            char mode[BUFSIZ];
            this->drwx(objFile.st_mode, mode);

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

    /*
     * drwx permission format
     *
     */
    void drwx(mode_t i, char *buf) {
        *buf++ = (i & S_IFDIR) ? 'd' : '-';
        *buf++ = (i & S_IRUSR) ? 'r' : '-';
        *buf++ = (i & S_IWUSR) ? 'w' : '-';
        *buf++ = (i & S_IXUSR) ? 'x' : '-';
        *buf++ = (i & S_IRGRP) ? 'r' : '-';
        *buf++ = (i & S_IWGRP) ? 'w' : '-';
        *buf++ = (i & S_IXGRP) ? 'x' : '-';
        *buf++ = (i & S_IROTH) ? 'r' : '-';
        *buf++ = (i & S_IWOTH) ? 'w' : '-';
        *buf++ = (i & S_IXOTH) ? 'x' : '-';
        *buf = '\0';
    }
};


class View {
public:
    /*
     * Print structure
     * maxlen have structure int maxlen_mode,maxlen_uid,maxlen_gid,maxlen_size,maxlen_time,maxlen_name
     */
    void print(vector< vector<string> > &dir_struct){
        char * print_string;
        int width;
        vector<int> maxlen;

        char s_format[100];

        for (int i =0; i<dir_struct[0].size(); i++){
            maxlen.push_back(0);
        }

        for (int i=0; i<dir_struct.size(); i++) {
            for (int j=0; j<dir_struct[i].size(); j++){
                if (dir_struct[i][j].length() > maxlen[j]){
                    maxlen[j] = dir_struct[i][j].length();
                }
            }
        }

        for (int i=0; i<dir_struct.size(); i++) {
            for (int j=0; j<dir_struct[i].size(); j++){
                print_string = new char[dir_struct[i][j].length() + 1];
                strcpy(print_string, dir_struct[i][j].c_str());
                width = maxlen[j] - dir_struct[i][j].length();

                sprintf(s_format, "%c%d%c", '%', maxlen[j]+3, 's');
                //printf(s_format,print_string);

                //sprintf(s_format, "%d", maxlen[j]);
                //printf("%s", s_format);
                printf(s_format,print_string);
            }
            printf("\n");
        }
    }
};

int main() {
    vector<string> lsdir;
    vector< vector<string> > dir_struct;

    Controller c;
    c.createlist(lsdir);

    Model m;
    m.create_struct(lsdir);
    dir_struct = m.StructDir;

    View v;
    v.print(dir_struct);
}
