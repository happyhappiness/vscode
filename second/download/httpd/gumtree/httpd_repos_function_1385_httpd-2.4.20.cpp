char *cache_strqtok(char *str, const char *sep, char **last)
{
    char *token;
    int quoted = 0;

    if (!str) {         /* subsequent call */
        str = *last;    /* start where we left off */
    }

    if (!str) {         /* no more tokens */
        return NULL;
    }

    /* skip characters in sep (will terminate at '\0') */
    while (*str && ap_strchr_c(sep, *str)) {
        ++str;
    }

    if (!*str) {        /* no more tokens */
        return NULL;
    }

    token = str;

    /* skip valid token characters to terminate token and
     * prepare for the next call (will terminate at '\0)
     * on the way, ignore all quoted strings, and within
     * quoted strings, escaped characters.
     */
    *last = token;
    while (**last) {
        if (!quoted) {
            if (**last == '\"' && !ap_strchr_c(sep, '\"')) {
                quoted = 1;
                ++*last;
            }
            else if (!ap_strchr_c(sep, **last)) {
                ++*last;
            }
            else {
                break;
            }
        }
        else {
            if (**last == '\"') {
                quoted = 0;
                ++*last;
            }
            else if (**last == '\\') {
                ++*last;
                if (**last) {
                    ++*last;
                }
            }
            else {
                ++*last;
            }
        }
    }

    if (**last) {
        **last = '\0';
        ++*last;
    }

    return token;
}