static int matches_aliases(server_rec *s, const char *host)
{
    int i;
    apr_array_header_t *names;

    /* match ServerName */
    if (!strcasecmp(host, s->server_hostname)) {
        return 1;
    }

    /* search all the aliases from ServerAlias directive */
    names = s->names;
    if (names) {
        char **name = (char **) names->elts;
        for (i = 0; i < names->nelts; ++i) {
            if(!name[i]) continue;
            if (!strcasecmp(host, name[i]))
                return 1;
        }
    }
    names = s->wild_names;
    if (names) {
        char **name = (char **) names->elts;
        for (i = 0; i < names->nelts; ++i) {
            if(!name[i]) continue;
            if (!ap_strcasecmp_match(host, name[i]))
                return 1;
        }
    }
    return 0;
}