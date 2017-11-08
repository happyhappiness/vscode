static const char *cmd_rewritecond_setflag(apr_pool_t *p,
                                           rewritecond_entry *cfg,
                                           char *key, char *val)
{
    if (   strcasecmp(key, "nocase") == 0
        || strcasecmp(key, "NC") == 0    ) {
        cfg->flags |= CONDFLAG_NOCASE;
    }
    else if (   strcasecmp(key, "ornext") == 0
             || strcasecmp(key, "OR") == 0    ) {
        cfg->flags |= CONDFLAG_ORNEXT;
    }
    else {
        return apr_pstrcat(p, "RewriteCond: unknown flag '", key, "'", NULL);
    }
    return NULL;
}