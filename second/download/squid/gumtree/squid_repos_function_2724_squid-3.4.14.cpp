char *
ConfigParser::strtokFile(void)
{
    static int fromFile = 0;
    static FILE *wordFile = NULL;
    LOCAL_ARRAY(char, undoToken, CONFIG_LINE_LIMIT);

    char *t, *fn;
    LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);

    if (!undo.empty()) {
        strncpy(undoToken, undo.front().c_str(), sizeof(undoToken));
        undoToken[sizeof(undoToken) - 1] = '\0';
        undo.pop();
        return lastToken = undoToken;
    }

    if (RecognizeQuotedValues)
        return lastToken = ConfigParser::NextToken();

    lastToken = NULL;
    do {

        if (!fromFile) {
            t = (strtok(NULL, w_space));

            if (!t || *t == '#') {
                return NULL;
            } else if (*t == '\"' || *t == '\'') {
                /* quote found, start reading from file */
                fn = ++t;

                while (*t && *t != '\"' && *t != '\'')
                    ++t;

                *t = '\0';

                if ((wordFile = fopen(fn, "r")) == NULL) {
                    debugs(28, DBG_CRITICAL, "strtokFile: " << fn << " not found");
                    return (NULL);
                }

#if _SQUID_WINDOWS_
                setmode(fileno(wordFile), O_TEXT);
#endif

                fromFile = 1;
            } else {
                return lastToken = t;
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

    return lastToken = t;
}