int reinstall(char* name) {
    checkroot();
    char *cache = combine("/etc/neptune/cache/", name, 0);
    char *app = combine("/etc/neptune/apps/", name, 0);
    link(app, cache);
    free(app);
    destroy(name);
    integrate(cache);
    free(cache);
    return 0;
}