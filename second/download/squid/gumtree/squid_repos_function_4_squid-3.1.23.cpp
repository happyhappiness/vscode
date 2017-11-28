static const char *
xstrtok(char **str, char del)
{
    if (*str) {
        char *p = strchr(*str, del);
        char *tok = *str;
        int len;

        if (p) {
            *str = p + 1;
            *p = '\0';
        } else
            *str = NULL;

        /* trim */
        len = strlen(tok);

        while (len && xisspace(tok[len - 1]))
            tok[--len] = '\0';

        while (xisspace(*tok))
            tok++;

        return tok;
    } else
        return "";
}