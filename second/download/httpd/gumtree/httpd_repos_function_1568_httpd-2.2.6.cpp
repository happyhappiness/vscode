static const char *filter_declare(cmd_parms *cmd, void *CFG, const char *fname,
                                  const char *place)
{
    mod_filter_cfg *cfg = (mod_filter_cfg *)CFG;
    ap_filter_rec_t *filter;

    filter = apr_pcalloc(cmd->pool, sizeof(ap_filter_rec_t));
    apr_hash_set(cfg->live_filters, fname, APR_HASH_KEY_STRING, filter);

    filter->name = fname;
    filter->filter_init_func = filter_init;
    filter->filter_func.out_func = filter_harness;
    filter->ftype = AP_FTYPE_RESOURCE;
    filter->next = NULL;

    if (place) {
        if (!strcasecmp(place, "CONTENT_SET")) {
            filter->ftype = AP_FTYPE_CONTENT_SET;
        }
        else if (!strcasecmp(place, "PROTOCOL")) {
            filter->ftype = AP_FTYPE_PROTOCOL;
        }
        else if (!strcasecmp(place, "CONNECTION")) {
            filter->ftype = AP_FTYPE_CONNECTION;
        }
        else if (!strcasecmp(place, "NETWORK")) {
            filter->ftype = AP_FTYPE_NETWORK;
        }
    }

    return NULL;
}