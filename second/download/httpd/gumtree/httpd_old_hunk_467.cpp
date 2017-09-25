                     "or is incomplete",
                     key);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    obj = apr_pcalloc(r->pool, sizeof(*obj));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(*dobj));

    obj->key = apr_pstrdup(r->pool, key);
    /* XXX Bad Temporary Cast - see cache_object_t notes */
    obj->info.len = (apr_size_t) len;
    obj->complete = 0;   /* Cache object is not complete */

    dobj->name = obj->key;

    /* open temporary file */
    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);
    rv = apr_file_mktemp(&tmpfile, dobj->tempfile,
                         APR_CREATE | APR_READ | APR_WRITE | APR_EXCL, r->pool);

    if (rv == APR_SUCCESS) {
        /* Populate the cache handle */
        h->cache_obj = obj;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Storing URL %s",  key);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Could not store URL %s [%d]", key, rv);

        return DECLINED;
    }

    return OK;
}

static int open_entity(cache_handle_t *h, request_rec *r, const char *key)
{
