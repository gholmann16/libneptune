int registerp(const char *softlink, char *ptr) {

    if (appimage_is_registered_in_system(softlink))
        appimage_unregister_in_system(softlink, VERBOSE); //in case you uninstall and reinstall Neptune
    
    appimage_register_in_system(softlink, VERBOSE);

    char *localdata = getdir("userdata");
    chdir(getenv("HOME"));
    chdir(".local/share/aisap/profiles");
    if(access(ptr, F_OK)) {
        FILE *perms = fopen(ptr, "w");
        fprintf(perms, "[X-App Permissions]\n");
        fprintf(perms, "Level=2\n");
        fprintf(perms, "Files=xdg-desktop;xdg-download:rw;/run/dbus;/run/user:rw;\n");
        fprintf(perms, "Devices=dri;\n");
        fprintf(perms, "Sockets=x11;wayland;pulseaudio;network;\n");
        fclose(perms);
    }

    chdir(getenv("HOME"));    
    mkdir(localdata, 0700);
    chdir(localdata);

    free(localdata);

    DIR* dir = opendir(ptr);

    if (dir) {
        /* Directory exists. */
        closedir(dir);
        printf("App has previously been installed, skipping user installation.\n");
        return 0;
    } 
    
    else {
        mkdir(ptr, 0700);     
        return 0;
    }
}

int deregister(char *name) { 
    return appimage_unregister_in_system(name, VERBOSE);
}
