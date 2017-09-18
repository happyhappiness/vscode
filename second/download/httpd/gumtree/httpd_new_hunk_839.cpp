    cache_read_entity_body(cache->handle, r->pool, bb);

    /* This filter is done once it has served up its content */
    ap_remove_output_filter(f);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                 "cache: serving %s", r->uri);
    return ap_pass_brigade(f->next, bb);
}


/*
 * CACHE_CONDITIONAL filter
