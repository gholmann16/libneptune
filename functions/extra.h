char* combine(const char* input1, const char* input2, int slash) {
    char* output = malloc(strlen(input1) + strlen(input2) + 1);
    if (slash)
        sprintf(output, "%s/%s", input1, input2);
    else 
        sprintf(output, "%s%s", input1, input2);
    return output;
}