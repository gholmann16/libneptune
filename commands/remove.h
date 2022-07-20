int destroy(char* file) {

    char *dir = getdir("/etc/neptune/dir");
    checkroot();

    char *link = combine("/etc/neptune/bin/", file, 0);
    char *app = combine("/etc/neptune/apps/", file, 0);
    char *real = combine(dir, file, 1);
    char *real2 = combine(real, ".desktop", 0);
    free(real);

    printf("Deregistering from system.\n");
    struct passwd *pwd;
    setpwent();

    while ((pwd = getpwent()) != NULL) {
        if(pwd->pw_uid > 999) {
            setenv("HOME", pwd->pw_dir, 1);
            seteuid(pwd->pw_uid);
            deregister(link);
            seteuid(0);
        }
    }
    remove(link);
    free(link);
    unregisterApp("/etc/neptune/list", file);
    remove(real2);
    if (remove(app) == 0)
        printf("Success\n");
    else {
        perror("Unable to delete app");
        printf("APP: %s\n", app);
    }
    free(app);
    free(real2);

    return 0;
}