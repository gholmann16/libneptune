char* searchxml(char* file) {
    char path[MAX_DIR_LEN];
    strcpy(path, getenv("HOME"));
    strcat(path, "/.config/neptune/mirror");
    ezxml_t mirror = ezxml_parse_file(path);
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

    if(!access(name, F_OK) && !check(name))
        return integrate(name);
    char file[MAX_DIR_LEN];
    strcpy(file, getenv("OWD"));
    strcat(file, "/");
    strcat(file, name);
    if(!access(file, F_OK ) && !check(file)) 
        return integrate(file);
    else if (download(name)) {
        char newfile[MAX_DIR_LEN];
        strcpy(newfile, "/tmp/");
        strcat(newfile, name);
        if(!check(newfile))
            return integrate(newfile);
        else 
            return remove(newfile);
    }
    return 0;
}