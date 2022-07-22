int list() {
    return system("cd /etc/neptune/apps && du --block-size=MB * | sort -hr");
}