int integrate(char * file) {

    char filenamecp[MAX_FILE_LENGTH];
    char finalfile[MAX_DIR_LEN];
    strcpy(filenamecp, file);

    chmod(file, PERMISSIONS);

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


    strcpy(finalfile, getenv("HOME"));
    strcat(finalfile, "/.local/neptune/apps/");
    strcat(finalfile, ptr);

    sexecl("/bin/mv", filenamecp, finalfile, NULL);
    
    printf("Registering into system.\n");

    char softlink[MAX_DIR_LEN];
    strcpy(softlink, getenv("HOME"));
    strcat(softlink, "/.local/neptune/bin/");
    strcat(softlink, ptr);
    remove(softlink);
    symlink(finalfile, softlink);
    
    registerp(softlink, ptr);

    remove(softlink);
    symlink("/usr/bin/nep", softlink);

    char dotdesktop[MAX_DIR_LEN];
    char *dir = getdir("dir");
    strcpy(dotdesktop, getenv("HOME"));
    strcat(dotdesktop, "/");
    strcat(dotdesktop, dir);
    strcat(dotdesktop, "/");
    strcat(dotdesktop, ptr);
    strcat(dotdesktop, ".desktop");

    free(dir);

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