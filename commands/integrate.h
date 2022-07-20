int integrate(char file[MAX_FILE_LENGTH]) {

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
    setpwent();

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) { 
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            registerp(softlink, ptr);
            seteuid(0);
        }
	}

    endpwent();

    remove(softlink);
    symlink("/etc/neptune/bin/nep", softlink);
    registerApp(ptr);

    char dotdesktop[MAX_DIR_LEN];
    strcpy(dotdesktop, getdir("/etc/neptune/dir"));
    strcat(dotdesktop, "/");
    strcat(dotdesktop, ptr);
    strcat(dotdesktop, ".desktop");

    char* dfile = desktop(finalfile);
    if (dfile == NULL)
        printf("Desktop file not found.");
    else {
        appimage_extract_file_following_symlinks(finalfile, dfile, dotdesktop);
        chmod(dotdesktop, 0755);
        printf("Success.\n");
    }

    free(dfile);
    return 0;
}