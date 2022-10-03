int uninstall(char *file) {
    //Delete App
    destroy(file);

    printf("App deleted from system. Are you sure you would like to uninstall all data?\n\033[0;31mIf you paid for this app or it contains important/irreplacable data, this data will be gone forever. \033[0m[y/N]: ");
    
    // Request Data Deletion
    char responce = getc(stdin);
    if (!(responce == 'y' || responce == 'Y')) {
        printf("Exiting without deleting data.\nIf you want to delete this data at a later date, you can go to your data folder and manually remove the folder for the app.\n");
        return 0;
    }
    
    // Delete Data
    char* home = getdir("userdata");
    chdir(getenv("HOME"));
    chdir(home);
    free(home);
    sexecl("/bin/rm", "-rf", file, NULL);

    printf("Data deleted.");
    
    return 0;
}