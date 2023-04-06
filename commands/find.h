int find(char* file) {
    if (file == NULL) return printf("No search term provided.\n");
    char path[MAX_DIR_LEN];
    strcpy(path, getenv("HOME"));
    strcat(path, "/.config/neptune/mirror");
    if (access(path, F_OK)) { 
        printf("Local mirror not availible. Downloading latest mirror.\n");
        update(2, NULL);
    }
    ezxml_t mirror = ezxml_parse_file(path);
    ezxml_t app;
    
    for (app = ezxml_child(mirror, "app"); app; app = app->next) {
        if (strstr(ezxml_attr(app, "name"), file)) {
            printf("\033[0;32m%s\033[0m/%s \033[1;31m(Size: %s)\033[0m\n\t%s\n", 
                ezxml_attr(app, "name"),
                ezxml_child(app, "version")->txt,
                ezxml_child(app, "size")->txt,
                ezxml_child(app, "description")->txt);
        }
    }
    ezxml_free(mirror);
    return 0;
}