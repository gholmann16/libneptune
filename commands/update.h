int update(int argc, char *name) {
    
    checkroot();

    if(argc == 2)  //if nep update is run, update refrences
        sexecl("/usr/bin/wget", "https://neptune.fr.to/mirror", "-O", "/etc/neptune/mirror");
    else { //otherwise update the app specified
        char *file = combine("/etc/neptune/apps", name, 1);
        if (!check(file)) update_appimage(file);
        free(file);
    }

    return 0;
}