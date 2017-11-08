char *shell_esc(const char *str)
{
    char *cmd;
    unsigned char *d;
    const unsigned char *s;

    cmd = (char *)malloc(2 * strlen(str) + 1);
    d = (unsigned char *)cmd;
    s = (const unsigned char *)str;

    for (; *s; ++s) {
        if (*s == '"' || *s == '\\') {
            *d++ = '\\';
        }
        *d++ = *s;
    }

    *d = '\0';
    return cmd;
}