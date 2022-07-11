int refresh() {
    checkroot();
    chdir("/etc/neptune/apps");
    system("ls > /etc/neptune/list");
    return 0;
}