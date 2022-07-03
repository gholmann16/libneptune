int run(char file[MAX_FILE_LENGTH], int argc, char * argv[]) {

    char dir1[MAX_DIR_LEN+1];
    char dir2[MAX_DIR_LEN+1];
    
    strncpy(dir1, "/etc/neptune/apps", MAX_DIR_LEN);
    strncpy(dir2, getdir("/etc/neptune/userdata"), MAX_DIR_LEN);
    dir1[MAX_DIR_LEN] = '\0';
    dir2[MAX_DIR_LEN] = '\0';
    
    char *program = combine(dir1, file, 1);
    char *location = combine(dir2, file, 1);
    int ret;

    if(!access(program, F_OK)) {
        char cmd[4096];
        sprintf(cmd, "aisap-0.6.6-alpha-x86_64.AppImage --profile %s/metadata/permissions.ini --data-dir %s/apphome %s", location, location, program);
        if(argc > 0)
            for (int i = 1; i < argc; i++) {
                strcat(cmd, " ");
                strncat(cmd, argv[i], strlen(argv[i]));
                printf("cmd %d = %s\n", i, cmd);
            }
        printf("cmd = %s", cmd);
        ret = system(cmd);
    }
    else {
        printf("This program (%s) does not exist.\n", program);
        ret = 8;
    }

    free(location); // we stan proper memory management 
    free(program);
    return ret;
}