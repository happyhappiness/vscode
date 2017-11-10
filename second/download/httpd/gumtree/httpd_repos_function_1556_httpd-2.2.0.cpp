static const char *filter_provider(cmd_parms *cmd, void *CFG, const char *args)
{
    mod_filter_cfg *cfg = CFG;
    int flags;
    ap_filter_provider_t *provider;
    const char *rxend;
    const char *c;
    char *str;
    const char *eq;
    ap_filter_rec_t* frec;
    ap_filter_rec_t* provider_frec;

    /* insist on exactly four arguments */
    const char *fname = ap_getword_conf(cmd->pool, &args) ;
    const char *pname = ap_getword_conf(cmd->pool, &args) ;
    const char *condition = ap_getword_conf(cmd->pool, &args) ;
    const char *match = ap_getword_conf(cmd->pool, &args) ;
    eq = ap_getword_conf(cmd->pool, &args) ;
    if ( !*fname || !*pname || !*match || !*condition || *eq ) {
        return "usage: FilterProvider filter provider condition match" ;
    }

    /* fname has been declared with DeclareFilter, so we can look it up */
    frec = apr_hash_get(cfg->live_filters, fname, APR_HASH_KEY_STRING);

    /* or if provider is mod_filter itself, we can also look it up */
    if (!frec) {
        c = filter_declare(cmd, CFG, fname, NULL);
        if ( c ) {
            return c;
        }
        frec = apr_hash_get(cfg->live_filters, fname, APR_HASH_KEY_STRING);
    }

    if (!frec) {
        return apr_psprintf(cmd->pool, "Undeclared smart filter %s", fname);
    }

    /* if provider has been registered, we can look it up */
    provider_frec = ap_get_output_filter_handle(pname);
    if (!provider_frec) {
        provider_frec = apr_hash_get(cfg->live_filters, pname,
                                     APR_HASH_KEY_STRING);
    }
    if (!provider_frec) {
        return apr_psprintf(cmd->pool, "Unknown filter provider %s", pname);
    }

    provider = apr_palloc(cmd->pool, sizeof(ap_filter_provider_t));
    if (*match == '!') {
        provider->not = 1;
        ++match;
    }
    else {
        provider->not = 0;
    }

    switch (*match++) {
    case '<':
        if (*match == '=') {
            provider->match_type = INT_LE;
            ++match;
        }
        else {
            provider->match_type = INT_LT;
        }
        provider->match.number = atoi(match);
        break;
    case '>':
        if (*match == '=') {
            provider->match_type = INT_GE;
            ++match;
        }
        else {
            provider->match_type = INT_GT;
        }
        provider->match.number = atoi(match);
        break;
    case '=':
        provider->match_type = INT_EQ;
        provider->match.number = atoi(match);
        break;
    case '/':
        provider->match_type = REGEX_MATCH;
        rxend = ap_strchr_c(match, '/');
        if (!rxend) {
              return "Bad regexp syntax";
        }
        flags = AP_REG_NOSUB;        /* we're not mod_rewrite:-) */
        for (c = rxend+1; *c; ++c) {
            switch (*c) {
            case 'i': flags |= AP_REG_ICASE; break;
            }
        }
        provider->match.regex = ap_pregcomp(cmd->pool,
                                            apr_pstrndup(cmd->pool,
                                                         match,
                                                         rxend-match),
                                            flags);
        break;
    case '*':
        provider->match_type = DEFINED;
        provider->match.number = -1;
        break;
    case '$':
        provider->match_type = STRING_CONTAINS;
        str = apr_pstrdup(cmd->pool, match);
        ap_str_tolower(str);
        provider->match.string = str;
        break;
    default:
        provider->match_type = STRING_MATCH;
        provider->match.string = apr_pstrdup(cmd->pool, match-1);
        break;
    }
    provider->frec = provider_frec;
    provider->next = frec->providers;
    frec->providers = provider;

    /* determine what a filter will dispatch this provider on */
    eq = ap_strchr_c(condition, '=');
    if (eq) {
        str = apr_pstrdup(cmd->pool, eq+1);
        if (!strncasecmp(condition, "env=", 4)) {
            provider->dispatch = SUBPROCESS_ENV;
        }
        else if (!strncasecmp(condition, "req=", 4)) {
            provi