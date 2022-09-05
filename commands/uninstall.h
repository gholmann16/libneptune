int uninstall(char *file) {
    //Delete App
    destroy(file);

    printf("App deleted from system. Are you sure you would like to uninstall all data?\n\033[0;31mIf you paid for this app or it contains important/irreplacable data, this data will be gone forever. \033[0m[y/N]: ");
    char responce;
    scanf("%c", &responce);
    if (!(responce == 'y' || responce == 'Y')) {
        printf("Exiting without deleting data.\nIf you want to delete this data at a later date, you can go to your data folder and manually remove the folder for the app.\n");
        return 0;
    }
    
    // Delete Data
    struct passwd *pwd;
    setpwent();

    char* home = getdir("/etc/neptune/userdata");
    memmove(home, home+2, strlen(home) + 2 - 1);

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            chdir(getenv("HOME"));
            chdir(home);
            sexecl("/bin/rm", "-rf", file, NULL);
            seteuid(0);
        }
    }

    printf("Data deleted.");
    
    return 0;
}