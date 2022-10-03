int update(int argc, char *name) {
    char file[MAX_DIR_LEN];
    strcpy(file, getenv("HOME"));
    if(argc == 2)  { //if nep update is run, update refrences
        strcat(file, "/.config/neptune/mirror");
        sexecl("/usr/bin/wget", "https://neptune.fr.to/mirror", "-O", file, NULL);
    }
    else { //otherwise update the app specified
        strcat(file, "/.local/neptune/apps/");
        strcat(file, name);
        if (!check(file)) 
            update_appimage(file);
    }

    return 0;
}