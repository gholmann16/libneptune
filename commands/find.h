int find(char* file) {
    char cmd[256];
    sprintf(cmd, "ls /etc/neptune/data | grep \"^%s\"", file);
    return system(cmd);
}