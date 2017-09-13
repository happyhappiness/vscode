static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
    int fd = STDIN_FILENO;
    int count;

    if (buflen == 0) {
        errno = EINVAL;
        return -1;
    }
    if (enableRawMode(fd) == -1) return -1;
    count = linenoisePrompt(fd, buf, buflen, prompt);
    disableRawMode(fd);
    printf("\n");
    return count;
}