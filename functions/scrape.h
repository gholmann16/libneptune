char *getdir(char * pdir) {

    char newdir[MAX_DIR_LEN];
    strcpy(newdir, getenv("HOME"));
    strcat(newdir, "/.config/neptune/");
    strcat(newdir, pdir);

    if(access(newdir, F_OK )) {
        printf("You have not selected your directory preferences yet. Run ./Neptune-x86_64.AppImage --install to install Neptune to your system");
        exit(1);
    }
    
    char * dir = malloc(MAX_DIR_LEN);
    char ch;
    int i = 0;
    FILE *fp = fopen(newdir, "r");
    while ((ch = fgetc(fp)) != EOF) {
        dir[i] = ch;
        ++i;
    }
    fclose(fp);
    return dir;
}

const char *getFileExtension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}