/*  Electron apps should have access to /run + /run/user:rw
    PDFstudio needs access to /etc/fonts
    libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)
    happens with or without sandboxing
    
    */
int permissions(int give, char* app, char* change) {
    if (app == NULL) {
        printf("\033[0;31mNo app name inputted.\033[0m\n");
        return 1;
    }

    if(change == NULL) {
        printf("\033[0;31mNo change inputted.\033[0m\n");
        return 1;
    }
    
    char perms[MAX_DIR_LEN];    

    strcpy(perms, getenv("HOME"));
    strcat(perms, "/.local/share/aisap/profiles/");
    strcat(perms, app);

    FILE * f = fopen(perms, "r+");
    if(f == NULL) {
        printf("Somehow you do not have a permissions file at %s. Were you poking around too much?\n", perms);
        return 1;
    }
    fpos_t position;
    fgetpos(f, &position);

    char permissions[4096] = {0};
    char str[512];
    int i;

    switch(give) {
        case 1: {
            for(i = 0; i < 3; i++) {
                fgets(str, 512, f);
                strcat(permissions, str);
            }
            permissions[strlen(permissions) - 1] = '\0';
            strcat(permissions, change);
            strcat(permissions, "\n");
            while(1) {
                if(fgets(str, 512, f) == NULL)
                    break;
                strcat(permissions, str);
            }

            printf("Added file permission %s to %s\n", change, app);
            break;
        }
        case -1: {
            for(i = 0; i < 2; i++) {
                fgets(str, 512, f);
                strcat(permissions, str);
            }

            fgets(str, 512, f);
            size_t len = strlen(change);
            char * p = str;
            while ((p = strstr(p, change)) != NULL) 
                memmove(p, p + len, strlen(p + len) + 1);
            strcat(permissions, str);

            while(1) {
                if(fgets(str, 512, f) == NULL)
                    break;
                strcat(permissions, str);
            }
            
            printf("Removed file permission %s from %s\n", change, app);
            break;
        }
        case 2: {
            for(i = 0; i < 5; i++) {
                fgets(str, 512, f);
                strcat(permissions, str);
            }
            permissions[strlen(permissions) - 1] = '\0';
            strcat(permissions, change);
            strcat(permissions, ";\n");

            printf("Added socket permission %s from %s\n", change, app);
            break;
        }
        case -2: {
            for(i = 0; i < 4; i++) {
                fgets(str, 512, f);
                strcat(permissions, str);
            }
            fgets(str, 512, f);

            char added[256];
            strcpy(added, change);
            strcat(added, ";");

            size_t len = strlen(added);
            char * p = str;
            while ((p = strstr(p, added)) != NULL) 
                memmove(p, p + len, strlen(p + len) + 1);
            strcat(permissions, str);

            printf("Removed socket permission %s from %s\n", change, app);
            break;
        }
        case 3: {
            for(i = 0; i < 3; i++) {
                fgets(str, 512, f);
                strcat(permissions, str);
            }
            fgets(str, 512, f);
            strcat(permissions, "Devices=dri;\n");
            fgets(str, 512, f);
            strcat(permissions, str);

            printf("Added dri permission to %s\n", app);
            break;
        }
        case -3: {
            for(i = 0; i < 3; i++) {
                fgets(str, 512, f);
                strcat(permissions, str);
            }
            fgets(str, 512, f);
            strcat(permissions, "Devices=\n");
            fgets(str, 512, f);
            strcat(permissions, str);

            printf("Removed dri permission from %s\n", app);
            break;
        }
        default: 
            printf("This line should NOT have been called you fucked something up");
            break;
    }

    fsetpos(f, &position);
    fprintf(f, permissions);
    
    // Got to remember to make the file smaller after removing permissions
    int fd = fileno(f);
    ftruncate(fd, strlen(permissions));

    fclose(f);

    return 0;
}