int bsexecl(const char * command, const char * args[]) {

    pid_t p=fork();
    if(p==0) {
        execv(command, (char * const *)args);
        perror("execv");
        exit(1);
    }
    waitpid(p, NULL, 0);
    return 0;
}

int sexecl(const char *command, ...) {
    va_list val;
    const char **args = NULL;
    int argc;
    int result;

    // Determine number of variadic arguments
    va_start(val, command);
    argc = 2; // leading command + trailing NULL
    while (va_arg(val, const char *) != NULL)
        argc++;
    va_end(val);
    args = (const char **) malloc(argc * sizeof(char*));

    // Allocate args, put references to command / variadic arguments + NULL in args
    args[0] = command;
    va_start(val, command);
    int i = 0;
    do {
        //fprintf(stderr, "Argument %i: %s\n", i, args[i]);
        i++;
        args[i] = va_arg(val, const char *);
    } while (args[i] != NULL);
    va_end(val);

    result = bsexecl(command, args);
    free(args);
    return result;
}