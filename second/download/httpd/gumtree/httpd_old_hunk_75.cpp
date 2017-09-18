        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "CACHE_OUT enabled unexpectedly");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
            "cache: running CACHE_OUT filter");

    /* TODO: Handle getting errors on either of these calls 
     * ???: Should we return headers on a subrequest?
     */
    cache_read_entity_headers(cache->handle, r);    
    cache_read_entity_body(cache->handle, r->pool, bb);

    /* This filter is done once it has served up its content */
    ap_remove_output_filter(f);

    ap_log_error(APLOG_MARK, APLOG_INFO | APLOG_NOERRNO, 0, r->server,
            "cached version of %s being served", r->uri);
    return ap_pass_brigade(f->next, bb);
}


/*
 * CACHE_CONDITIONAL filter
