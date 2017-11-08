char *shell_esc(const char *str)
{
    int in_quote = 0;
    char *cmd;
    unsigned char *d;
    const unsigned char *s;

    cmd = (char *)malloc(2 * strlen(str) + 1);
    d = (unsigned char *)cmd;
    s = (const unsigned char *)str;

    for (; *s; ++s) {
        if (*s == '"') {
            *d++ = '\\';
            in_quote++;
        }
        else if (*s == '\\' || (*s == ' ' && (in_quote % 2))) {
            *d++ = '\\';
        }
        *d++ = *s;
    }

    *d = '\0';
    return cmd;
}