char * name(char * path) {
    char * file = desktop(path);
    if (file == NULL) {
        printf("Desktop file not found.");
        free(file);
        return NULL;
    }
    appimage_extract_file_following_symlinks(path, file, "/tmp/desktopfile");
    free(file);
    FILE * temp = fopen("/tmp/desktopfile", "r");
    char* line = malloc(1000);
    char find[6] = {'N', 'a', 'm', 'e', '=', '\0'};
    while(fgets(line, 1000, temp)!= NULL) /* read a line from a file */ {
        char needle[6] = {line[0], line[1], line[2], line[3], line[4], '\0'};
        if(!strcmp(find, needle))
            break;
    }
    memmove (line, line+5, strlen(line) - 5 + 1);
    line[strlen(line) - 1] = '\0';
    fclose(temp);
    remove("/tmp/desktopfile"); 
    return line;
}