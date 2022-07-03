int reinstall(char* name) {
    checkroot();
    char *cache = combine("/etc/neptune/cache/", name, 0);
    destroy(name);
    integrate(cache);
    free(cache);
    return 0;
}