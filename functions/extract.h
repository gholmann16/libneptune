char* desktop(char *path) {
    char **array = appimage_list_files(path);
    int i = 0;
    while (array[i] != NULL) {
        if (strcmp(getFileExtension(array[i]), "desktop") == 0) {
            char * answer = malloc(MAX_FILE_LENGTH);
            strcpy(answer, array[i]);
            appimage_string_list_free(array);
            return answer;
        }
        i++;
    }
    appimage_string_list_free(array);
    return NULL; //not found;
}

char* icon(char *path) {
    char **array = appimage_list_files(path);
    int i = 0;
    while (array[i] != NULL) {
        if (strcmp(array[i], ".DirIcon") == 0) {
            char * answer = malloc(MAX_FILE_LENGTH);
            strcpy(answer, array[i]);
            appimage_string_list_free(array);
            return answer;
        }
        i++;
    }
    appimage_string_list_free(array);
    return NULL; //not found
}

char* metadata(char *path) {
    char **array = appimage_list_files(path);
    int i = 0;
    while (array[i] != NULL) {
        char * pointer = array[i];
        if (strcmp(pointer + strlen(pointer) - 11, "appdata.xml") == 0) {
            char * answer = malloc(MAX_FILE_LENGTH);
            strcpy(answer, array[i]);
            appimage_string_list_free(array);
            return answer;
        }
        i++;
    }
    appimage_string_list_free(array);
    return NULL; //not found
}