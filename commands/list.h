int list() {
    return system("cd ~/.local/neptune/apps && du --block-size=MB * | sort -hr");
}