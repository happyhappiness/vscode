static apr_status_t cache_filter(ap_filter_t *f, apr_bucket_brigade *in)
{

    cache_server_conf
            *conf =
                    (cache_server_conf *) ap_get_module_config(f->r->server->module_config,
                            &cache_module);

    /* was the quick handler enabled */
    if (conf->quick) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r, APLOGNO(00776)
                "cache: CACHE filter was added in quick handler mode and "
                "will be ignored: %s", f->r->unparsed_uri);
    }
    /* otherwise we may have been bypassed, nothing to see here */
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(00777)
                "cache: CACHE filter was added twice, or was added where "
                "the cache has been bypassed and will be ignored: %s",
                f->r->unparsed_uri);
    }

    /* we are just a marker, so let's just remove ourselves */
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}