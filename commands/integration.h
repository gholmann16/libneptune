int integrate(char file[MAX_FILE_LENGTH]) {

    char* dir = getdir("/etc/neptune/dir");
    checkroot();

    char filenamecp[MAX_FILE_LENGTH];
    char finalfile[MAX_DIR_LEN];
    strcpy(filenamecp, file);

    chown(file, 0, 0);
    chmod(file, 0755);

    // Don't add part after -
    char *ptr;

    ptr = strchr(file, '-');
    if (ptr != NULL)
        *ptr = '\0';
    else if(strcmp(getFileExtension(file), "AppImage") == 0)
        file[strlen(file)-9] = '\0';

    ptr = strrchr(file, '/');
    if (ptr == NULL) 
        ptr = file; 
        // this used to be a much simpler function
        //idk if c library updated or sum but this shit is bloated
    else 
        ptr = ptr + 1;


    strcpy(finalfile, "/etc/neptune/apps/");
    strcat(finalfile, ptr);

    sexecl("/bin/mv", filenamecp, finalfile, NULL);
    
    printf("Registering into system.\n");

    char * softlink = combine("/etc/neptune/bin", ptr, 1);
    remove(softlink);
    symlink(finalfile, softlink);
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            registerp(softlink, ptr);
        }
	}

    remove(softlink);
    symlink("/etc/neptune/bin/nep", softlink);
    free(softlink);
    registerApp(ptr);

    if (desktop(finalfile)) {
        printf("Desktop file not found.");
        return 0; //I'm going to start returning 0 so long as the program finishes
    }
    
    strcpy(finalfile, dir);
    strcat(finalfile, "/");
    strcat(finalfile, ptr);
    strcat(finalfile, ".desktop");

    sexecl("/bin/cp", getdir("/tmp/filepath"), finalfile, NULL);
    chmod(finalfile, 0755);
    remove("/tmp/filepath");

    return 0;
}

int destroy(char file[MAX_FILE_LENGTH]) {

    char *dir = getdir("/etc/neptune/dir");
    checkroot();

    char *real = combine(dir, file, 1);
    char *real2 = combine(real, ".desktop", 1);
    char *link = combine("/etc/neptune/bin/", file, 0);
    char *app = combine("/etc/neptune/apps/", file, 0);
    char *cache = combine("/etc/neptune/cache/", file, 0);
    printf("Deregistering from system.\n");
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            deregister(link);
        }
    }
    remove(link);
    unregisterApp("/etc/neptune/list", file);
    remove(real2);
    if (rename(app, cache) == 0)
        printf("Success\n");
    else
        perror("Unable to cache the file\n");
    free(link); //holy shit properly using my memory? what am I some kind of kernel dev??
    free(real);
    free(app);
    free(real2);
    free(cache);
    return 0;
}