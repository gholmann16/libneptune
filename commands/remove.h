int destroy(char* file) {

    if(file == NULL) {
        printf("No app name inputted.\n");
        exit(1);
    }

    char link[MAX_DIR_LEN];
    char app[MAX_DIR_LEN];
    char real[MAX_DIR_LEN];
    
    strcpy(link, getenv("HOME"));
    strcat(link, "/.local/neptune/bin/");
    strcat(link, file);

    strcpy(app, getenv("HOME"));
    strcat(app, "/.local/neptune/apps/");
    strcat(app, file);

    strcpy(real, getenv("HOME"));
    char *dir = getdir("dir");
    strcat(real, "/");
    strcat(real, dir);
    strcat(real, "/");
    strcat(real, file);
    strcat(real, ".desktop");
    free(dir);

    printf("Deregistering from system.\n");
    deregister(link);

    remove(link);
    remove(real);
    if (remove(app) == 0)
        printf("Success\n");
    else {
        perror("Unable to delete app");
        printf("APP: %s\n", app);
    }

    return 0;
}