int list() {
    return system("du --block-size=MB /etc/neptune/apps/* | sort -hr");
}