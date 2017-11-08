static const char *cmd_rewriterule_setflag(apr_pool_t *p,
                                           rewriterule_entry *cfg,
                                           char *key, char *val)
{
    int status = 0;
    int i;

    if (   strcasecmp(key, "redirect") == 0
        || strcasecmp(key, "R") == 0       ) {
        cfg->flags |= RULEFLAG_FORCEREDIRECT;
        if (strlen(val) > 0) {
            if (strcasecmp(val, "permanent") == 0) {
                status = HTTP_MOVED_PERMANENTLY;
            }
            else if (strcasecmp(val, "temp") == 0) {
                status = HTTP_MOVED_TEMPORARILY;
            }
            else if (strcasecmp(val, "seeother") == 0) {
                status = HTTP_SEE_OTHER;
            }
            else if (apr_isdigit(*val)) {
                status = atoi(val);
            }
            if (!ap_is_HTTP_REDIRECT(status)) {
                return "RewriteRule: invalid HTTP response code "
                       "for flag 'R'";
            }
            cfg->forced_responsecode = status;
        }
    }
    else if (   strcasecmp(key, "noescape") == 0
        || strcasecmp(key, "NE") == 0       ) {
        cfg->flags |= RULEFLAG_NOESCAPE;
    }
    else if (   strcasecmp(key, "last") == 0
             || strcasecmp(key, "L") == 0   ) {
        cfg->flags |= RULEFLAG_LASTRULE;
    }
    else if (   strcasecmp(key, "next") == 0
             || strcasecmp(key, "N") == 0   ) {
        cfg->flags |= RULEFLAG_NEWROUND;
    }
    else if (   strcasecmp(key, "chain") == 0
             || strcasecmp(key, "C") == 0    ) {
        cfg->flags |= RULEFLAG_CHAIN;
    }
    else if (   strcasecmp(key, "type") == 0
             || strcasecmp(key, "T") == 0   ) {
        cfg->forced_mimetype = apr_pstrdup(p, val);
        ap_str_tolower(cfg->forced_mimetype);
    }
    else if (   strcasecmp(key, "env") == 0
             || strcasecmp(key, "E") == 0   ) {
        for (i = 0; (cfg->env[i] != NULL) && (i < MAX_ENV_FLAGS); i++)
            ;
        if (i < MAX_ENV_FLAGS) {
            cfg->env[i] = apr_pstrdup(p, val);
            cfg->env[i+1] = NULL;
        }
        else {
            return "RewriteRule: too many environment flags 'E'";
        }
    }
    else  if ( strcasecmp(key, "cookie") == 0 || strcasecmp(key, "CO") == 0) {
        for (i = 0; (cfg->cookie[i] != NULL) && (i < MAX_COOKIE_FLAGS); i++)
            ;
        if (i < MAX_COOKIE_FLAGS) {
            cfg->cookie[i] = apr_pstrdup(p, val);
            cfg->cookie[i+1] = NULL;
        }
        else {
            return "RewriteRule: too many cookie flags 'CO'";
        }
    }
    else if (   strcasecmp(key, "nosubreq") == 0
             || strcasecmp(key, "NS") == 0      ) {
        cfg->flags |= RULEFLAG_IGNOREONSUBREQ;
    }
    else if (   strcasecmp(key, "proxy") == 0
             || strcasecmp(key, "P") == 0      ) {
        cfg->flags |= RULEFLAG_PROXY;
    }
    else if (   strcasecmp(key, "passthrough") == 0
             || strcasecmp(key, "PT") == 0      ) {
        cfg->flags |= RULEFLAG_PASSTHROUGH;
    }
    else if (   strcasecmp(key, "skip") == 0
             || strcasecmp(key, "S") == 0   ) {
        cfg->skip = atoi(val);
    }
    else if (   strcasecmp(key, "forbidden") == 0
             || strcasecmp(key, "F") == 0   ) {
        cfg->flags |= RULEFLAG_FORBIDDEN;
    }
    else if (   strcasecmp(key, "gone") == 0
             || strcasecmp(key, "G") == 0   ) {
        cfg->flags |= RULEFLAG_GONE;
    }
    else if (   strcasecmp(key, "qsappend") == 0
             || strcasecmp(key, "QSA") == 0   ) {
        cfg->flags |= RULEFLAG_QSAPPEND;
    }
    else if (   strcasecmp(key, "nocase") == 0
             || strcasecmp(key, "NC") == 0    ) {
        cfg->flags |= RULEFLAG_NOCASE;
    }
    else {
        return apr_pstrcat(p, "RewriteRule: unknown flag '", key, "'", NULL);
    }
    return NULL;
}