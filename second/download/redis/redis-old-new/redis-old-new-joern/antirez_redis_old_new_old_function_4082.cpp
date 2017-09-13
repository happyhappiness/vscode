char *linenoise(const char *prompt) {
    char buf[LINENOISE_MAX_LINE];
    int count;

    count = linenoiseRaw(buf,LINENOISE_MAX_LINE,prompt);
    if (count == -1) return NULL;
    return strdup(buf);
}