BOOL ssl_util_vhost_matches(const char *servername, server_rec *s)
{
    apr_array_header_t *names;
    int i;
    
    /* check ServerName */
    if (!strcasecmp(servername, s->server_hostname)) {
        return TRUE;
    }
    
    /*
     * if not matched yet, check ServerAlias entries
     * (adapted from vhost.c:matches_aliases())
     */
    names = s->names;
    if (names) {
        char **name = (char **)names->elts;
        for (i = 0; i < names->nelts; ++i) {
            if (!name[i])
                continue;
            if (!strcasecmp(servername, name[i])) {
                return TRUE;
            }
        }
    }
    
    /* if still no match, check ServerAlias entries with wildcards */
    names = s->wild_names;
    if (names) {
        char **name = (char **)names->elts;
        for (i = 0; i < names->nelts; ++i) {
            if (!name[i])
                continue;
            if (!ap_strcasecmp_match(servername, name[i])) {
                return TRUE;
            }
        }
    }
    
    return FALSE;
}