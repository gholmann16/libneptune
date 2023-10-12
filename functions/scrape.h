char *getdir(char * pdir) {

    char newdir[MAX_DIR_LEN];
    strcpy(newdir, getenv("HOME"));
    strcat(newdir, "/.config/neptune/");
    strcat(newdir, pdir);
    
    char * dir = malloc(MAX_DIR_LEN);
    char ch;
    int i = 0;
    FILE *fp = fopen(newdir, "r");
    while ((ch = fgetc(fp)) != EOF) {
        dir[i] = ch;
        ++i;
    }
    dir[i] = '\0';
    fclose(fp);
    return dir;
}

const char *getFileExtension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}