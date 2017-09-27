                     "or is incomplete",
                     key);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(*obj));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(*dobj));

    obj->key = apr_pstrdup(r->pool, key);
    /* XXX Bad Temporary Cast - see cache_object_t notes */
    obj->info.len = (apr_size_t) len;
    obj->complete = 0;   /* Cache object is not complete */

    dobj->name = obj->key;
    dobj->datafile = data_file(r->pool, conf, dobj, key);
    dobj->hdrsfile = header_file(r->pool, conf, dobj, key);
    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);

    return OK;
}

static int open_entity(cache_handle_t *h, request_rec *r, const char *key)
{
