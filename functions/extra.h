char* combine(const char* input1, const char* input2, int slash) {
    char* output = malloc(MAX_DIR_LEN);
    if (slash)
        sprintf(output, "%s/%s", input1, input2);
    else 
        sprintf(output, "%s%s", input1, input2);
    return output;
}