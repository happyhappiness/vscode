void
print_esc(FILE * p, char *s)
{
    char buf[HELPER_INPUT_BUFFER];
    char *t;
    int i = 0;

    for (t = s; *t != '\0'; ++t) {
        /*
         * NP: The shell escaping permits 'i' to jump up to 2 octets per loop,
         *     so ensure we have at least 3 free.
         */
        if (i > HELPER_INPUT_BUFFER-3) {
            buf[i] = '\0';
            (void) fputs(buf, p);
            i = 0;
        }
        if (*t == '\\')
            buf[i++] = '\\';

        buf[i] = *t;
        ++i;
    }

    if (i > 0) {
        buf[i] = '\0';
        (void) fputs(buf, p);
    }
}