static int
get_token(register FILE *fp, register char *token)
{
    register int ch;
    register char *cp = token;
    register int hash = 0;
    register struct tok *tp;

    *cp = 0;
    ch = (unsigned char)last;
    /* skip all white space */
    while (xisspace(ch) && ch != -1) {
        ch = getc(fp);
        if (ch == '\n')
            Line++;
    }
    if (ch == -1)
        return ENDOFFILE;

    /*
     * Accumulate characters until end of token is found.  Then attempt to match this
     * token as a reserved word.  If a match is found, return the type.  Else it is
     * a label.
     */
    do {
        if (ch == '\n')
            Line++;
        if (xisspace(ch) || ch == '(' || ch == ')' ||
                ch == '{' || ch == '}' || ch == ',' ||
                ch == '"') {
            if (!xisspace(ch) && *token == 0) {
                hash += ch;
                *cp++ = ch;
                last = ' ';
            } else {
                last = ch;
            }
            *cp = '\0';

            for (tp = buckets[BUCKET(hash)]; tp; tp = tp->next) {
                if ((tp->hash == hash) && (strcmp(tp->name, token) == 0))
                    break;
            }
            if (tp) {
                if (tp->token == CONTINUE)
                    continue;
                return (tp->token);
            }
            if (token[0] == '-' && token[1] == '-') {
                /* strip comment */
                while ((ch = getc(fp)) != -1)
                    if (ch == '\n') {
                        Line++;
                        break;
                    }
                if (ch == -1)
                    return ENDOFFILE;
                last = ch;
                return get_token(fp, token);
            }
            for (cp = token; *cp; cp++)
                if (!xisdigit(*cp))
                    return LABEL;
            return NUMBER;
        } else {
            hash += ch;
            *cp++ = ch;
            if (ch == '\n')
                Line++;
        }

    } while ((ch = getc(fp)) != -1);
    return ENDOFFILE;
}