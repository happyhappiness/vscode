void
print_esc(FILE * p, char *s)
{
    char buf[256];
    char *t;
    int i = 0;

    for (t = s; *t != '\0'; t++) {
        if (i > 250) {
            buf[i] = '\0';
            (void) fputs(buf, p);
            i = 0;
        }
        if (*t == '\\')
            buf[i++] = '\\';

        buf[i++] = *t;
    }

    if (i > 0) {
        buf[i] = '\0';
        (void) fputs(buf, p);
    }
}