int uninstall(char *file) {
    //Delete App
    destroy(file);

    // Delete Data
    char* directory[4] = {"apphome/.local/share", "apphome/.config", "apphome/.cache"};
    struct passwd *pwd;
    setpwent();
    int i;

    char* home = getdir("/etc/neptune/userdata");
    memmove(home, home+2, strlen(home) + 2 - 1);

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            chdir(getenv("HOME"));
            chdir(home);
            chdir(file);
            for (i = 0; i < 3; i++) 
                sexecl("/bin/rm", "-rf", directory[i], NULL);
            seteuid(0);
        }
    }
    
    return 0;
}