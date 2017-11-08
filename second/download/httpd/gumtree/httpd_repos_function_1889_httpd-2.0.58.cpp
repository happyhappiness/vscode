static char *find_fqdn(apr_pool_t *a, struct hostent *p)
{
    int x;

    if (!strchr(p->h_name, '.')) {
        if (p->h_aliases) {
            for (x = 0; p->h_aliases[x]; ++x) {
                if (strchr(p->h_aliases[x], '.') &&
                    (!strncasecmp(p->h_aliases[x], p->h_name,
                                  strlen(p->h_name))))
                    return apr_pstrdup(a, p->h_aliases[x]);
            }
        }
        return NULL;
    }
    return apr_pstrdup(a, (void *) p->h_name);
}