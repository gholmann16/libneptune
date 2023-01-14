int upgrade() {
    char location[512];
    strcpy(location, getenv("HOME"));
    strcat(location, "/.local/neptune/apps/");

    DIR *d;
    struct dirent *dir;
    d = opendir(location);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
                if (updatable(dir->d_name)) {
                    update(0, dir->d_name);
                }
            }
        }
        closedir(d);
    }

    return 0;
}