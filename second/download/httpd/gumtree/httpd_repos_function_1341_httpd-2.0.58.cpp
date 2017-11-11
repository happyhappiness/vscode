static void decodehtml(char *s)
{
    int val, i, j;
    char *p;
    const char *ents;
    static const char * const entlist[MAXENTLEN + 1] =
    {
        NULL,                   /* 0 */
        NULL,                   /* 1 */
        "lt\074gt\076",         /* 2 */
        "amp\046ETH\320eth\360",        /* 3 */
        "quot\042Auml\304Euml\313Iuml\317Ouml\326Uuml\334auml\344euml\353\
iuml\357ouml\366uuml\374yuml\377",      /* 4 */
        "Acirc\302Aring\305AElig\306Ecirc\312Icirc\316Ocirc\324Ucirc\333\
THORN\336szlig\337acirc\342aring\345aelig\346ecirc\352icirc\356ocirc\364\
ucirc\373thorn\376",            /* 5 */
        "Agrave\300Aacute\301Atilde\303Ccedil\307Egrave\310Eacute\311\
Igrave\314Iacute\315Ntilde\321Ograve\322Oacute\323Otilde\325Oslash\330\
Ugrave\331Uacute\332Yacute\335agrave\340aacute\341atilde\343ccedil\347\
egrave\350eacute\351igrave\354iacute\355ntilde\361ograve\362oacute\363\
otilde\365oslash\370ugrave\371uacute\372yacute\375"     /* 6 */
    };

    /* Do a fast scan through the string until we find anything
     * that needs more complicated handling
     */
    for (; *s != '&'; s++) {
        if (*s == '\0') {
            return;
        }
    }

    for (p = s; *s != '\0'; s++, p++) {
        if (*s != '&') {
            *p = *s;
            continue;
        }
        /* find end of entity */
        for (i = 1; s[i] != ';' && s[i] != '\0'; i++) {
            continue;
        }

        if (s[i] == '\0') {     /* treat as normal data */
            *p = *s;
            continue;
        }

        /* is it numeric ? */
        if (s[1] == '#') {
            for (j = 2, val = 0; j < i && apr_isdigit(s[j]); j++) {
                val = val * 10 + s[j] - '0';
            }
            s += i;
            if (j < i || val <= 8 || (val >= 11 && val <= 31) ||
                (val >= 127 && val <= 160) || val >= 256) {
                p--;            /* no data to output */
            }
            else {
                *p = RAW_ASCII_CHAR(val);
            }
        }
        else {
            j = i - 1;
            if (j > MAXENTLEN || entlist[j] == NULL) {
                /* wrong length */
                *p = '&';
                continue;       /* skip it */
            }
            for (ents = entlist[j]; *ents != '\0'; ents += i) {
                if (strncmp(s + 1, ents, j) == 0) {
                    break;
                }
            }

            if (*ents == '\0') {
                *p = '&';       /* unknown */
            }
            else {
                *p = RAW_ASCII_CHAR(((const unsigned char *) ents)[j]);
                s += i;
            }
        }
    }

    *p = '\0';
}