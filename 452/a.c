    #include <stdio.h>
    #include <dirent.h>

    int main (int c, char *v[]) {
        int len;
        struct dirent *pDirent;
        DIR *pDir;

        if (c < 2) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }
        pDir = opendir (v[1]);
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", v[1]);
            return 1;
        }

        while ((pDirent = readdir(pDir)) != NULL) {
            printf ("[%s] type=%d\n", pDirent->d_name, (int)pDirent->d_type);
        }
        closedir (pDir);
        return 0;
    }
