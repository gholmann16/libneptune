int download(char file[MAX_FILE_LENGTH]) {
    char *url = combine("/etc/neptune/data/", file, 0);
    char *temp = combine("/tmp/", file, 0);
    if(access(url, F_OK )) {
        printf("No program (%s) found in database or directory. ", file);
        printf("If you have not updated it in a while or this is your accessing it, run nep update to update your local program database.\n");
        free(url);
        free(temp);
        return 0;
    }
    char cmd[2048];
    sprintf(cmd, "/usr/bin/wget -i %s -q --show-progress -O %s", url, temp);
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
    if(st.st_size > 0) {
        free(url);
        free(temp);
        return 1; //successful, 1 here means it worked
    }
    else {
        printf("File download failed.\n");
        remove(temp);
        printf("Contents of %s database file:\n", file);
        sexecl("/bin/cat", url, NULL, NULL);
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