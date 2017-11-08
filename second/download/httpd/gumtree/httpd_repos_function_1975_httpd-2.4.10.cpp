static char *de_socketfy(apr_pool_t *p, char *url)
{
    char *ptr;
    /*
     * We could be passed a URL during the config stage that contains
     * the UDS path... ignore it
     */
    if (!strncasecmp(url, "unix:", 5) &&
        ((ptr = ap_strchr(url, '|')) != NULL)) {
        /* move past the 'unix:...|' UDS path info */
        char *ret, *c;

        ret = ptr + 1;
        /* special case: "unix:....|scheme:" is OK, expand
         * to "unix:....|scheme://localhost"
         * */
        c = ap_strchr(ret, ':');
        if (c == NULL) {
            return NULL;
        }
        if (c[1] == '\0') {
            return apr_pstrcat(p, ret, "//localhost", NULL);
        }
        else {
            return ret;
        }
    }
    return url;
}