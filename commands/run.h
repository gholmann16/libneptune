int run(char file[MAX_FILE_LENGTH], int argc, char * argv[]) {

    char dir1[MAX_DIR_LEN];
    char dir2[MAX_DIR_LEN];
    
    strcpy(dir1, "/etc/neptune/apps/");
    strcpy(dir2, getdir("/etc/neptune/userdata"));
    
    strcat(dir1, file);
    char *location = combine(dir2, file, 1);
    int ret;
    int i;

    if(!access(dir1, F_OK)) {
        char cmd[4096];
        sprintf(cmd, "aisap-0.6.6-alpha-x86_64.AppImage --profile %s/metadata/permissions.ini --data-dir %s/apphome %s", location, location, dir1);
        if(argc > 0)
            for (i = 1; i < argc; i++) {
                strcat(cmd, " ");
                strncat(cmd, argv[i], strlen(argv[i]));
            }
        ret = system(cmd);
    }
    else {
        printf("This program (%s) does not exist.\n", dir1);
        ret = 8;
    }

    free(location); // we stan proper memory management 
    return ret;
}