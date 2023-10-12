int run(char file[MAX_FILE_LENGTH], int argc, char * argv[]) {

    char app[MAX_FILE_LENGTH];
    char data[MAX_FILE_LENGTH];

    strcpy(app, getenv("HOME"));
    strcat(app, "/.local/neptune/apps/");
    strcat(app, file);


    if(access(app, F_OK)) {
        printf("This program (%s) does not exist.\n", app);
        exit(1);
    }

    char *dir = getdir("userdata");
    strcpy(data, getenv("HOME"));
    strcat(data, "/");
    strcat(data, dir);
    strcat(data, "/");
    strcat(data, file);
    free(dir);

    aisap_AppImage new;
    aisap_new_appimage(&new, app);
    strcpy(new.data_dir, data);

    aisap_appimage_sandbox(&new, 0, NULL);
    aisap_appimage_mount(&new);
    aisap_appimage_run(&new, NULL);

    aisap_appimage_destroy(&new);
    
    return 0;
}