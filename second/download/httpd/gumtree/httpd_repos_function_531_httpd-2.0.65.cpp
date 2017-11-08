static char *check_code(apr_pool_t *p, const char *code, char **real_code)
{
    char *word;
    char base = 'X';
    int modifier = 0;
    int num = 0;
    int factor = 0;

    /* 0.0.4 compatibility?
     */
    if ((code[0] == 'A') || (code[0] == 'M')) {
        *real_code = (char *)code;
        return NULL;
    }

    /* <base> [plus] {<num> <type>}*
     */

    /* <base>
     */
    word = ap_getword_conf(p, &code);
    if (!strncasecmp(word, "now", 1) ||
        !strncasecmp(word, "access", 1)) {
        base = 'A';
    }
    else if (!strncasecmp(word, "modification", 1)) {
        base = 'M';
    }
    else {
        return apr_pstrcat(p, "bad expires code, unrecognised <base> '",
                       word, "'", NULL);
    }

    /* [plus]
     */
    word = ap_getword_conf(p, &code);
    if (!strncasecmp(word, "plus", 1)) {
        word = ap_getword_conf(p, &code);
    }

    /* {<num> <type>}*
     */
    while (word[0]) {
        /* <num>
         */
        if (apr_isdigit(word[0])) {
            num = atoi(word);
        }
        else {
            return apr_pstrcat(p, "bad expires code, numeric value expected <num> '",
                           word, "'", NULL);
        }

        /* <type>
         */
        word = ap_getword_conf(p, &code);
        if (word[0]) {
            /* do nothing */
        }
        else {
            return apr_pstrcat(p, "bad expires code, missing <type>", NULL);
        }

        factor = 0;
        if (!strncasecmp(word, "years", 1)) {
            factor = 60 * 60 * 24 * 365;
        }
        else if (!strncasecmp(word, "months", 2)) {
            factor = 60 * 60 * 24 * 30;
        }
        else if (!strncasecmp(word, "weeks", 1)) {
            factor = 60 * 60 * 24 * 7;
        }
        else if (!strncasecmp(word, "days", 1)) {
            factor = 60 * 60 * 24;
        }
        else if (!strncasecmp(word, "hours", 1)) {
            factor = 60 * 60;
        }
        else if (!strncasecmp(word, "minutes", 2)) {
            factor = 60;
        }
        else if (!strncasecmp(word, "seconds", 1)) {
            factor = 1;
        }
        else {
            return apr_pstrcat(p, "bad expires code, unrecognised <type>",
                           "'", word, "'", NULL);
        }

        modifier = modifier + factor * num;

        /* next <num>
         */
        word = ap_getword_conf(p, &code);
    }

    *real_code = apr_psprintf(p, "%c%d", base, modifier);

    return NULL;
}