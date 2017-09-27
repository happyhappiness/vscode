       return OK;
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00691)
                 "cache: Removing url %s from the cache", h->cache_obj->key);

    /* for each specified cache type, delete the URL */
    while(list) {
        list->provider->remove_url(h, r);
        list = list->next;
    }
    return OK;
}

