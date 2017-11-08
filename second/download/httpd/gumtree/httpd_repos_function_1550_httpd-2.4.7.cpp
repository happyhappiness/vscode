static const char *cmd_rewritecond_setflag(apr_pool_t *p, void *_cfg,
                                           char *key, char *val)
{
    rewritecond_entry *cfg = _cfg;

    if (   strcasecmp(key, "nocase") == 0
        || strcasecmp(key, "NC") == 0    ) {
        cfg->flags |= CONDFLAG_NOCASE;
    }
    else if (   strcasecmp(key, "ornext") == 0
             || strcasecmp(key, "OR") == 0    ) {
        cfg->flags |= CONDFLAG_ORNEXT;
    }
    else if (   strcasecmp(key, "novary") == 0
             || strcasecmp(key, "NV") == 0    ) {
        cfg->flags |= CONDFLAG_NOVARY;
    }
    else {
        return apr_pstrcat(p, "unknown flag '", key, "'", NULL);
    }
    return NULL;
}