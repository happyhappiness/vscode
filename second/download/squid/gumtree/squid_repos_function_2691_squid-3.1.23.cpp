char *
ConfigParser::strtokFile(void)
{
    static int fromFile = 0;
    static FILE *wordFile = NULL;

    char *t, *fn;
    LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);

    do {

        if (!fromFile) {
            t = (strtok(NULL, w_space));

            if (!t || *t == '#') {
                return NULL;
            } else if (*t == '\"' || *t == '\'') {
                /* quote found, start reading from file */
                fn = ++t;

                while (*t && *t != '\"' && *t != '\'')
                    t++;

                *t = '\0';

                if ((wordFile = fopen(fn, "r")) == NULL) {
                    debugs(28, 0, "strtokFile: " << fn << " not found");
                    return (NULL);
                }

#ifdef _SQUID_WIN32_
                setmode(fileno(wordFile), O_TEXT);

#endif

                fromFile = 1;
            } else {
                return t;
            }
        }

        /* fromFile */
        if (fgets(buf, CONFIG_LINE_LIMIT, wordFile) == NULL) {
            /* stop reading from file */
            fclose(wordFile);
            wordFile = NULL;
            fromFile = 0;
            return NULL;
        } else {
            char *t2, *t3;
            t = buf;
            /* skip leading and trailing white space */
            t += strspn(buf, w_space);
            t2 = t + strcspn(t, w_space);
            t3 = t2 + strspn(t2, w_space);

            while (*t3 && *t3 != '#') {
                t2 = t3 + strcspn(t3, w_space);
                t3 = t2 + strspn(t2, w_space);
            }

            *t2 = '\0';
        }

        /* skip comments */
        /* skip blank lines */
    } while ( *t == '#' || !*t );

    return t;
}