static void read_quoted(char **string, char **quoted_part)
{
    char *strp = *string;

    /* assume there's no quoted part */
    *quoted_part = NULL;

    while (apr_isspace(*strp)) {
        strp++;                 /* go along string until non-whitespace */
    }

    if (*strp == '"') {         /* if that character is a double quote */
        strp++;                 /* step over it */
        *quoted_part = strp;    /* note where the quoted part begins */

        while (*strp && *strp != '"') {
            ++strp;             /* skip the quoted portion */
        }

        *strp = '\0';           /* end the string with a NUL */

        strp++;                 /* step over the last double quote */
        *string = strp;
    }
}