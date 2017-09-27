        rv = file_cache_el_final(conf, &dobj->hdrs, r);
    }
    if (APR_SUCCESS == rv) {
        rv = file_cache_el_final(conf, &dobj->vary, r);
    }
    if (APR_SUCCESS == rv) {
        rv = file_cache_el_final(conf, &dobj->data, r);
    }

    /* remove the cached items completely on any failure */
    if (APR_SUCCESS != rv) {
        remove_url(h, r);
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00736)
