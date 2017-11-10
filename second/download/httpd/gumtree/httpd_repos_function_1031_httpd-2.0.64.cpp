static int parseargline(char *str, char **a1, char **a2, char **a3)
{
    char *cp;
    int isquoted;

#define SKIP_WHITESPACE(cp) \
    for ( ; *cp == ' ' || *cp == '\t'; ) { \
        cp++; \
    };

#define CHECK_QUOTATION(cp,isquoted) \
    isquoted = 0; \
    if (*cp == '"') { \
        isquoted = 1; \
        cp++; \
    }

#define DETERMINE_NEXTSTRING(cp,isquoted) \
    for ( ; *cp != '\0'; cp++) { \
        if (   (isquoted    && (*cp     == ' ' || *cp     == '\t')) \
            || (*cp == '\\' && (*(cp+1) == ' ' || *(cp+1) == '\t'))) { \
            cp++; \
            continue; \
        } \
        if (   (!isquoted && (*cp == ' ' || *cp == '\t')) \
            || (isquoted  && *cp == '"')                  ) { \
            break; \
        } \
    }

    cp = str;
    SKIP_WHITESPACE(cp);

    /*  determine first argument */
    CHECK_QUOTATION(cp, isquoted);
    *a1 = cp;
    DETERMINE_NEXTSTRING(cp, isquoted);
    if (*cp == '\0') {
        return 1;
    }
    *cp++ = '\0';

    SKIP_WHITESPACE(cp);

    /*  determine second argument */
    CHECK_QUOTATION(cp, isquoted);
    *a2 = cp;
    DETERMINE_NEXTSTRING(cp, isquoted);
    if (*cp == '\0') {
        *cp++ = '\0';
        *a3 = NULL;
        return 0;
    }
    *cp++ = '\0';

    SKIP_WHITESPACE(cp);

    /* again check if there are only two arguments */
    if (*cp == '\0') {
        *cp++ = '\0';
        *a3 = NULL;
        return 0;
    }

    /*  determine second argument */
    CHECK_QUOTATION(cp, isquoted);
    *a3 = cp;
    DETERMINE_NEXTSTRING(cp, isquoted);
    *cp++ = '\0';

    return 0;
}