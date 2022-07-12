int check(char file[MAX_FILE_LENGTH]) {
    if (appimage_get_type(file, VERBOSE) == -1) {
        printf("%s is not an AppImage.\n", file);
        return 1;
    }
    else 
        return 0;
}