int update(int argc, char *name) {
    
    checkroot();

    if(argc == 2)  //if nep update is run, update refrences
        sexecl("/usr/bin/wget", "https://neptune.fr.to/mirror", "-O", "/etc/neptune/mirror");
    else { //otherwise update the app specified
        char *file = combine("/etc/neptune/apps", name, 1);
        if (!check(file)) {
            char *old = combine(file, ".zs-old", 0);
            char *updatetool = combine(getenv("APPDIR"), "/usr/bin/appimageupdatetool-x86_64.AppImage", 0);
            sexecl(updatetool, "-O", file, NULL);
            free(updatetool);
            if( access(old, F_OK ) == 0 ) {
                remove(old);
                printf("%s sucessfully updated!\n", name);
            }
            else 
                printf("No updates found.\n");
            free(old);
        }
        free(file);
    }

    return 0;
}