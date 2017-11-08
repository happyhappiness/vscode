static const char *filter_protocol(cmd_parms *cmd, void *CFG, const char *fname,
                                   const char *pname, const char *proto)
{
    static const char *sep = ";, \t";
    char *arg;
    char *tok = 0;
    unsigned int flags = 0;
    mod_filter_cfg *cfg = CFG;
    ap_filter_provider_t *provider = NULL;
    ap_filter_rec_t *filter = apr_hash_get(cfg->live_filters, fname,
                                           APR_HASH_KEY_STRING);

    if (!filter) {
        return "FilterProtocol: No such filter";
    }

    /* Fixup the args: it's really pname that's optional */
    if (proto == NULL) {
        proto = pname;
        pname = NULL;
    }
    else {
        /* Find provider */
        for (provider = filter->providers; provider; provider = provider->next){
            if (!strcasecmp(provider->frec->name, pname)) {
                break;
            }
        }
        if (!provider) {
            return "FilterProtocol: No such provider for this filter";
        }
    }

    /* Now set flags from our args */
    for (arg = apr_strtok(apr_pstrdup(cmd->pool, proto), sep, &tok);
         arg; arg = apr_strtok(NULL, sep, &tok)) {

        if (!strcasecmp(arg, "change=yes")) {
            flags |= AP_FILTER_PROTO_CHANGE | AP_FILTER_PROTO_CHANGE_LENGTH;
        }
        if (!strcasecmp(arg, "change=no")) {
            flags &= ~(AP_FILTER_PROTO_CHANGE | AP_FILTER_PROTO_CHANGE_LENGTH);
        }
        else if (!strcasecmp(arg, "change=1:1")) {
            flags |= AP_FILTER_PROTO_CHANGE;
        }
        else if (!strcasecmp(arg, "byteranges=no")) {
            flags |= AP_FILTER_PROTO_NO_BYTERANGE;
        }
        else if (!strcasecmp(arg, "proxy=no")) {
            flags |= AP_FILTER_PROTO_NO_PROXY;
        }
        else if (!strcasecmp(arg, "proxy=transform")) {
            flags |= AP_FILTER_PROTO_TRANSFORM;
        }
        else if (!strcasecmp(arg, "cache=no")) {
            flags |= AP_FILTER_PROTO_NO_CACHE;
        }
    }

    if (pname) {
        provider->frec->proto_flags = flags;
    }
    else {
        filter->proto_flags = flags;
    }

    return NULL;
}