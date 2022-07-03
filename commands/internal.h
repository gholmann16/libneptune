int registerp(char *softlink, char *ptr) {
    if (strcmp(getenv("HOME"), "/") == 0) {
        return 10; //this is for nobody user
    }

    if (appimage_is_registered_in_system(softlink))
        appimage_unregister_in_system(softlink, VERBOSE); //in case you uninstall and reinstall Neptune
    
    appimage_register_in_system(softlink, VERBOSE);
    char rlocaldata[MAX_DIR_LEN];
    char localdata[MAX_DIR_LEN];
    strncpy(rlocaldata, getdir("/etc/neptune/userdata"), MAX_DIR_LEN-1);
    rlocaldata[MAX_DIR_LEN] = '\0';
    for (int i = 0; i < strlen(rlocaldata); i++)
        localdata[i] = rlocaldata[i+2]; //could be problematic
    char* full = combine(getenv("HOME"), localdata, 1);
    mkdir(full, 0700);
    chdir(full);
    free(full);
    DIR* dir = opendir(ptr);

    if (dir) {
        /* Directory exists. */
        closedir(dir);
        printf("App already installed on this user, skipping installation.\n");
        return 9;
    } 
    
    else {
        mkdir(ptr, 0700);
        chdir(ptr);
        mkdir("metadata", 0700);
        mkdir("apphome", 0700);
        // mkdir("appcopy", 0700);
        
        FILE *perms = fopen("metadata/permissions.ini", "w");
        fprintf(perms, "[X-App Permissions]\n");
        fprintf(perms, "Level=2\n");
        fprintf(perms, "Files=xdg-desktop;xdg-download:rw;\n");
        fprintf(perms, "Devices=dri;\n");
        fprintf(perms, "Sockets=x11;wayland;pulseaudio;network;\n");
        fclose(perms);

        // link(combine("appcopy/", ptr, 0), combine(getdir("/etc/neptune/dir"), ptr, 1));
        // the link is to make it easy to transfer these appimages
        // might implement some more functionality after I make sandboxing mandatory
        return 0;
    }
}

int deregister(char *name) { //TODO: delete data dir 
    if (strcmp(getenv("HOME"), "/") == 0) {
        return 10; //this is for nobody user
    }
    return appimage_unregister_in_system(name, VERBOSE);
}

int uninstall() {
    printf("You should not have accessed this function.\n"); //uninstall data
    return 0;
}

int desktop(char *name) {
    char **array = appimage_list_files(name);
    int i = 0;
    while (array[i] != NULL) {
        if (strcmp(getFileExtension(array[i]), "desktop") == 0) {
            FILE *desktop = fopen("/tmp/filepath", "w");
            fprintf(desktop, "%s", array[i]);
            fclose(desktop);
            return 0;
        }
        i++;
    }
    return 1; //not found;
}