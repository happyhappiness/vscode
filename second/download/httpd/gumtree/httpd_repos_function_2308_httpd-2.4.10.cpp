static const char *filter_debug(cmd_parms *cmd, void *CFG, const char *fname,
                                const char *level)
{
    mod_filter_cfg *cfg = CFG;
    ap_filter_rec_t *frec = apr_hash_get(cfg->live_filters, fname,
                                         APR_HASH_KEY_STRING);
    if (!frec) {
        return apr_psprintf(cmd->pool, "Undeclared smart filter %s", fname);
    }
    frec->debug = atoi(level);

    return NULL;
}