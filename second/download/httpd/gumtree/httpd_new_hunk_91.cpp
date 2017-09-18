    h->read_body = &read_body;
    h->read_headers = &read_headers;
    h->write_body = &write_body;
    h->write_headers = &write_headers;
    h->remove_entity = &remove_entity;

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Caching URL %s",  key);

    return OK;
}

static int open_entity(cache_handle_t *h, request_rec *r, const char *type, const char *key)
