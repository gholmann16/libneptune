int run(char file[MAX_FILE_LENGTH], int argc, char * argv[]) {

    char app[MAX_DIR_LEN];
    char data[MAX_DIR_LEN];
    
    strcpy(app, getenv("HOME"));
    strcat(app, "/.local/neptune/apps/");
    strcat(app, file);
    
    char * dir = getdir("userdata");
    strcpy(data, getenv("HOME"));
    strcat(data, "/");
    strcat(data, dir);
    strcat(data, "/");
    strcat(data, file);
    free(dir);


    if(!access(app, F_OK)) {
        //sexecl("aisap-0.8.0-alpha-x86_64.AppImage", "--profile", permissions, "--data-dir", home, app);
        const char * arguments[argc + 4];
        int i;

        arguments[0] = "aisap-0.8.0-alpha-x86_64.AppImage";
        arguments[1] = "--data-dir";
        arguments[2] = data;
        arguments[3] = app;

        char command[MAX_DIR_LEN];
        strcpy(command, getenv("APPDIR"));
        strcat(command, "/usr/bin/");
        strcat(command, "aisap-0.8.0-alpha-x86_64.AppImage");

        for (i = 1; i < argc; i++)
            arguments[i + 3] = argv[i];
        arguments[argc + 3] = NULL;

        bsexecl(command, arguments);
        
    }
    else
        printf("This program (%s) does not exist.\n", app);

    return 0;
}