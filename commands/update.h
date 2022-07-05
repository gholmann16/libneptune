int update(int argc, char *name) {
    
    checkroot();

    if(argc == 2)  //if nep update is run, update refrences
        system("cd /tmp\ngit clone --depth 1 --filter=blob:none --sparse https://github.com/AppImage/appimage.github.io \ncd appimage.github.io\ngit sparse-checkout init --cone\ngit sparse-checkout set data\nrm -rf /etc/neptune/data\nmv /tmp/appimage.github.io/data /etc/neptune\ncd /etc/neptune/data\nfor f in *; do\n\ttest -f \"$f\" && mv \"$f\" \"${f,,}\" &>/dev/null\ndone\nrm -rf /tmp/appimage.github.io");
    else { //otherwise update the app specified
        char *file = combine("/etc/neptune/apps", name, 1);
        if (check(file)) {
            char *old = combine(file, ".zs-old", 0);
            char *oldloc = combine("/etc/neptune/apps/", old, 0);
            free(old);
            char *current = combine("/etc/neptune/apps/", file, 0);
            char *updatetool = combine(getenv("APPDIR"), "/usr/bin/appimageupdatetool-x86_64.AppImage", 0);
            sexecl(updatetool, "-O", current, NULL);
            free(current);
            free(updatetool);
            if( access(oldloc, F_OK ) == 0 ) 
                sexecl("/bin/rm", oldloc, NULL, NULL);
            free(oldloc);
        }
        free(file);
    }

    return 0;
}