int install_preferences() {

    //Essentially if data dir does not exist, install Neptune

    chdir(getenv("HOME"));

    mkdir(".config/neptune", PERMISSIONS);
    mkdir(".local/neptune", PERMISSIONS);
    mkdir(".local/neptune/bin", PERMISSIONS);
    mkdir(".local/neptune/apps", PERMISSIONS);
    mkdir(".cache/neptune", PERMISSIONS);
    mkdir(".cache/neptune/apps", PERMISSIONS);
    mkdir(".cache/neptune/featured", PERMISSIONS);
    mkdir("Applications", PERMISSIONS);
    mkdir(".AppImageData", 0700);

    FILE *applications = fopen(".config/neptune/dir", "w");
    fputs("Applications", applications);
    fclose(applications);

    FILE *userdata = fopen(".config/neptune/userdata", "w");
    fputs(".AppImageData", userdata);
    fclose(userdata);

    //If I can make this shell independent Neptune can be installed by a singular user
    FILE *path = fopen(".bash_profile", "a");
    fputs("export PATH=~/.local/neptune/bin:$PATH\n", path);
    fclose(path);

    return 0;

}

int remove_preferences() {

    chdir(getenv("HOME"));
    
    sexecl("/usr/bin/sed", "-i", "/neptune/d", ".bash_profile", NULL);

    //Leaves directory in case user has apps there
    //this function needs to be fixed lfmaoooo

    remove(".config/neptune/dir");
    remove(".config/neptune/userdata");
    
    return 0;
}