int integrate(char * file) {

    char filenamecp[MAX_FILE_LENGTH];
    char finalfile[MAX_DIR_LEN];
    strcpy(filenamecp, file);

    chmod(file, PERMISSIONS);

    char *ptr = name(file);

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
    char* dfile = appimage_registered_desktop_file_path(softlink, appimage_get_md5(softlink), 1);

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
    free(ptr);

    link(dfile, dotdesktop);
    chmod(dotdesktop, 0755);
    printf("Success.\n");

    return 0;
}