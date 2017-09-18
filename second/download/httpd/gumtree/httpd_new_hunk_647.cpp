
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Serving Cached URL %s",  dobj->name);
    return OK;
}

static int remove_entity(cache_handle_t *h) 
{
    /* Null out the cache object pointer so next time we start from scratch  */
    h->cache_obj = NULL;
    return OK;
}
