int reinstall(char* name) {
    char cache[MAX_DIR_LEN];
    char app[MAX_DIR_LEN];

    strcpy(cache, "/tmp/");
    strcat(cache, name);

    strcpy(app, getenv("HOME"));
    strcat(app, "/.local/neptune/apps/");
    strcat(app, name);

    link(app, cache);
    destroy(name);
    integrate(cache);
    return 0;
}