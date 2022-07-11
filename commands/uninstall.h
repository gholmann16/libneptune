int removedir() {
    return 0;
}

int uninstall(char* file[MAX_FILE_LENGTH]) {
    //Delete App
    unistall(file);

    // Delete Data
    char directory[4] = {"/metadata", "apphome/.local/share", "apphome/.config", "apphome/.cache"};
    struct passwd *pwd;
    int i;
    for (i = 0; i < 4; i++)
    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            removedir(directory[i]);
        }
	}
    seteuid(0);
    
    return 0;
}