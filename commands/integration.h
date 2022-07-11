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

    char softlink[384];
    strcpy(softlink, "/etc/neptune/bin/");
    strcat(softlink, ptr);
    remove(softlink);
    symlink(finalfile, softlink);
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            printf("vars = %s, %s, %d, %d, %d\n", getenv("HOME"), softlink, geteuid(), pwd->pw_uid, appimage_is_registered_in_system(softlink));
            registerp(softlink, ptr);
            seteuid(0);
        }
	}

    remove(softlink);
    symlink("/etc/neptune/bin/nep", softlink);
    registerApp(ptr);

    char dotdesktop[MAX_DIR_LEN];
    strcpy(dotdesktop, dir);
    strcat(dotdesktop, "/");
    strcat(dotdesktop, ptr);
    strcat(dotdesktop, ".desktop");

    char* dfile = desktop(finalfile);
    if (dfile == NULL)
        printf("Desktop file not found.");
    else {
        appimage_extract_file_following_symlinks(finalfile, dfile, dotdesktop);
        chmod(finalfile, 0755);
    }

    free(dfile);
    return 0;
}

int destroy(char file[MAX_FILE_LENGTH]) {

    char *dir = getdir("/etc/neptune/dir");
    checkroot();

    char *link = combine("/etc/neptune/bin/", file, 0);
    char *app = combine("/etc/neptune/apps/", file, 0);
    char *real = combine(dir, file, 1);
    char *real2 = combine(real, ".desktop", 1);
    free(real);

    printf("Deregistering from system.\n");
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            deregister(link);
            seteuid(0);
        }
    }
    remove(link);
    free(link);
    unregisterApp("/etc/neptune/list", file);
    remove(real2);
    if (remove(app) == 0)
        printf("Success\n");
    else {
        perror("Unable to delete app");
        printf("APP: %s\n", app);
    }
    free(app);
    free(real2);

    return 0;
}