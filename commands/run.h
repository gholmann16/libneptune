int run(char file[MAX_FILE_LENGTH], int argc, char * argv[]) {

    char app[MAX_DIR_LEN];
    char data[MAX_DIR_LEN];
    char permissions[MAX_DIR_LEN];
    char home[MAX_DIR_LEN];
    
    strcpy(app, "/etc/neptune/apps/");
    strcpy(data, getenv("HOME"));
    
    strcat(app, file);

    strcat(data, "/");
    strcat(data, getdir("/etc/neptune/userdata"));
    strcat(data, "/");
    strcat(data, file);

    strcpy(permissions, data);
    strcat(permissions, "/metadata/permissions.ini");

    strcpy(home, data);
    strcat(home, "/apphome"); 

    if(!access(app, F_OK)) {
        //sexecl("aisap-0.8.0-alpha-x86_64.AppImage", "--profile", permissions, "--data-dir", home, app);
        const char * arguments[argc + 6];
        int i;

        arguments[0] = "aisap-0.8.0-alpha-x86_64.AppImage";
        arguments[1] = "--profile";
        arguments[2] = permissions;
        arguments[3] = "--data-dir";
        arguments[4] = home;
        arguments[5] = app;

        char command[MAX_DIR_LEN];
        strcpy(command, getenv("APPDIR"));
        strcat(command, "/usr/bin/");
        strcat(command, "aisap-0.8.0-alpha-x86_64.AppImage");

        for (i = 1; i < argc; i++) 
            arguments[i + 5] = argv[i];
        arguments[argc + 5] = NULL;
        
        bsexecl(command, arguments);
        
    }
    else 
        printf("This program (%s) does not exist.\n", app);

    return 0;
}