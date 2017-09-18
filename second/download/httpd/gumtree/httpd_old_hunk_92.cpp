    h->read_body = &read_body;
    h->read_headers = &read_headers;
    h->write_body = &write_body;
    h->write_headers = &write_headers;
    h->remove_entity = &remove_entity;

    ap_log_error(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r->server,
                 "disk_cache: Serving Cached URL %s",  dobj->name);
    return OK;
}

static int remove_url(const char *type, char *key) 
{
  return OK;
}

static int remove_entity(cache_handle_t *h) 
{
    cache_object_t *obj = h->cache_obj;

    /* Null out the cache object pointer so next time we start from scratch  */
    h->cache_obj = NULL;
    return OK;
}

/*
