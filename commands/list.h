int list() {
    char location[MAX_DIR_LEN];
    strcpy(location, getenv("HOME"));
    strcat(location, "/.local/neptune/apps/");

    DIR *d;
    struct dirent *dir;
    d = opendir(location);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {

                char tmp[MAX_DIR_LEN];
                strcpy(tmp, location);
                strcat(tmp, dir->d_name);

                struct stat st;
                stat(tmp, &st);
                char decimals[32];
                sprintf(decimals, "%ld", st.st_size);
                int d, r, l;
                for (r = 0; r < 32; r++)
                    if (decimals[r] == '\0') 
                        break;
                d = r % 3;
                switch(d) {
                    case 1:
                        l = decimals[0] - 48;
                        break;
                    case 2:
                        l = 10 * (decimals[0] - 48);
                        l = l + decimals[1] - 48;
                        break;
                    case 0:
                        d = 3;
                        l = 100 * (decimals[0] - 48);
                        l = l + 10 * (decimals[1] - 48);
                        l = l + decimals[2] - 48;
                        break;
                }
                char power[3] = {0, 'B', 0};
                switch(r - d) {
                    case 3:
                        power[0] = 'K';
                        break;
                    case 6:
                        power[0] = 'M';
                        break;
                    case 9:
                        power[0] = 'B';
                        break;
                    case 12:
                        power[0] = 'T';
                        break;
                }

                char check[4] = {0, 0, 0, 0};
                if (updatable(dir->d_name)) {
                    check[0] = 226;
                    check[1] = 156;
                    check[2] = 147;
                }
                printf("%d%s\t%s\t%s\n", l, power, dir->d_name, check);
            }
        }
        closedir(d);
    }

    return 0;
}