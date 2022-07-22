char* searchxml(char* file) {
    ezxml_t mirror = ezxml_parse_file("/etc/neptune/mirror");
    ezxml_t app;
    
    for (app = ezxml_child(mirror, "app"); app; app = app->next) {
        if (strcmp(ezxml_attr(app, "name"), file) == 0) {
            printf("\033[0;32mPackage Found!\033[0m\n\ts%s (Size: %s)\033[0m\n", 
                ezxml_attr(app, "name"),
                ezxml_child(app, "size")->txt);
        char * ret = malloc(MAX_FILE_LENGTH);
        strcpy(ret, ezxml_child(app, "download")->txt);
        ezxml_free(mirror);
        return ret;
        }
    }
    ezxml_free(mirror);
    return NULL;
}

int download(char file[MAX_FILE_LENGTH]) {
    char *temp = combine("/tmp/", file, 0);
    char *url = searchxml(file);
    if(url == NULL) {
        printf("No program (%s) found in database or directory. ", file);
        printf("If you have not updated it in a while or this is your accessing it, run nep update to update your local program database.\n");
        free(url);
        free(temp);
        return 0;
    }
    char cmd[2048];
    sprintf(cmd, "wget %s -q --show-progress -O %s", url, temp);
    system(cmd);
    if(access(temp, F_OK )) {
        free(url);
        free(temp);
        printf("File download failed.\n");
        exit(5); //idk when this is supposed to happen
                 //prolly bad internet?
    }
    struct stat st;
    stat(temp, &st);
    if(st.st_size > 0) { //Measure if the file is larger than 0 bytes
        free(url);
        free(temp);
        return 1; //successful, 1 here means it worked
    }
    else { //If not, download failed
        printf("File download failed.\n");
        remove(temp);
        printf("Attempted to download from: %s\n", url);
        return 0;
    }
}

int install(char *name) {

    checkroot();

    int ret = 2;
    char *file = combine(getenv("OWD"), name, 1);

    if(!access(file, F_OK ) && !check(file)) 
        ret = integrate(file);
    else if(!access(name, F_OK) && !check(name))
        ret = integrate(name);
    else if (download(name)) {
        char *newfile = combine("/tmp/", name, 0);
        if(!check(newfile))
            ret = integrate(newfile);
        else 
            remove(newfile);
        free(newfile);
    }
    free(file);
    return ret;
}