int
main()
{
    char buf[BUFFER_SIZE];
    char *s, *t;
    int tlu = 0;

    /* make standard output line buffered */
    if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)
        return 1;

    /* speed up the access() calls below */
    if (chdir(ACCESS_LOCAL_DIR) == -1)
        return 1;

    /* scan standard input */
    while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        /* check for too long urls */
        if (strchr(buf, '\n') == NULL) {
            tlu = 1;
            continue;
        }
        if (tlu)
            goto dont_redirect;

        /* determine end of url */
        if ((s = strchr(buf, ' ')) == NULL)
            goto dont_redirect;
        *s = '\0';

        /* determine first character of filename */
        if ((s = strrchr(buf, '/')) == NULL)
            goto dont_redirect;
        s++;

        /* security: do not redirect to hidden files, the current
         * directory or the parent directory */
        if (*s == '.' || *s == '\0')
            goto dont_redirect;

        /* map filename to lower case */
        for (t = s; *t != '\0'; t++)
            *t = (char) tolower((int) *t);

        /* check for a local copy of this file */
        if (access(s, R_OK) == 0) {
            (void) printf("%s/%s\n", REDIRECT_TO_URL, s);
            continue;
        }
dont_redirect:
        tlu = 0;
        (void) printf("\n");
    }

    return 0;
}