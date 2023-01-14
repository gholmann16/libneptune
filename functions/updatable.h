int updatable(char * appname) {
    char file[MAX_DIR_LEN];
    strcpy(file, getenv("HOME"));
    strcat(file, "/.local/neptune/apps/");
    strcat(file, appname);
    return check_updateability(file);
}