static apr_status_t store_headers(cache_handle_t *h, request_rec *r,
        cache_info *info)
{
    cache_socache_dir_conf *dconf =
            ap_get_module_config(r->per_dir_config, &cache_socache_module);
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
            &cache_socache_module);
    apr_size_t slider;
    apr_status_t rv;
    cache_object_t *obj = h->cache_obj;
    cache_socache_object_t *sobj = (cache_socache_object_t*) obj->vobj;
    cache_socache_info_t *socache_info;

    memcpy(&h->cache_obj->info, info, sizeof(cache_info));

    if (r->headers_out) {
        sobj->headers_out = ap_cache_cacheable_headers_out(r);
    }

    if (r->headers_in) {
        sobj->headers_in = ap_cache_cacheable_headers_in(r);
    }

    sobj->expire
            = obj->info.expire > r->request_time + dconf->maxtime ? r->request_time
                    + dconf->maxtime
                    : obj->info.expire + dconf->mintime;

    apr_pool_create(&sobj->pool, r->pool);

    sobj->buffer = apr_palloc(sobj->pool, dconf->max);
    sobj->buffer_len = dconf->max;
    socache_info = (cache_socache_info_t *) sobj->buffer;

    if (sobj->headers_out) {
        const char *vary;

        vary = apr_table_get(sobj->headers_out, "Vary");

        if (vary) {
            apr_array_header_t* varray;
            apr_uint32_t format = CACHE_SOCACHE_VARY_FORMAT_VERSION;

            memcpy(sobj->buffer, &format, sizeof(format));
            slider = sizeof(format);

            memcpy(sobj->buffer + slider, &obj->info.expire,
                    sizeof(obj->info.expire));
            slider += sizeof(obj->info.expire);

            varray = apr_array_make(r->pool, 6, sizeof(char*));
            tokens_to_array(r->pool, vary, varray);

            if (APR_SUCCESS != (rv = store_array(varray, sobj->buffer,
                    sobj->buffer_len, &slider))) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02370)
                        "buffer too small for Vary array, caching aborted: %s",
                        obj->key);
                apr_pool_destroy(sobj->pool);
                sobj->pool = NULL;
                return rv;
            }
            if (socache_mutex) {
                apr_status_t status = apr_global_mutex_lock(socache_mutex);
                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02371)
                            "could not acquire lock, ignoring: %s", obj->key);
                    apr_pool_destroy(sobj->pool);
                    sobj->pool = NULL;
                    return status;
                }
            }
            rv = conf->provider->socache_provider->store(
                    conf->provider->socache_instance, r->server,
                    (unsigned char *) obj->key, strlen(obj->key), sobj->expire,
                    (unsigned char *) sobj->buffer, (unsigned int) slider,
                    sobj->pool);
            if (socache_mutex) {
                apr_status_t status = apr_global_mutex_unlock(socache_mutex);
                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02372)
                            "could not release lock, ignoring: %s", obj->key);
                }
            }
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(02373)
                        "Vary not written to cache, ignoring: %s", obj->key);
                apr_pool_destroy(sobj->pool);
                sobj->pool = NULL;
                return rv;
            }

            obj->key = sobj->key = regen_key(r->pool, sobj->headers_in, varray,
                    sobj->name);
        }
    }

    socache_info->format = CACHE_SOCACHE_DISK_FORMAT_VERSION;
    socache_info->date = obj->info.date;
    socache_info->expire = obj->info.expire;
    socache_info->entity_version = sobj->socache_info.entity_version++;
    socache_info->request_time = obj->info.request_time;
    socache_info->response_time = obj->info.response_time;
    socache_info->status = obj->info.status;

    if (r->header_only && r->status != HTTP_NOT_MODIFIED) {
        socache_info->header_only = 1;
    }
    else {
        socache_info->header_only = sobj->socache_info.header_only;
    }

    socache_info->name_len = strlen(sobj->name);

    memcpy(&socache_info->control, &obj->info.control, sizeof(cache_control_t));
    slider = sizeof(cache_socache_info_t);

    if (slider + socache_info->name_len >= sobj->buffer_len) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02374)
                "cache buffer too small for name: %s",
                sobj->name);
        apr_pool_destroy(sobj->pool);
        sobj->pool = NULL;
        return APR_EGENERAL;
    }
    memcpy(sobj->buffer + slider, sobj->name, socache_info->name_len);
    slider += socache_info->name_len;

    if (sobj->headers_out) {
        if (APR_SUCCESS != store_table(sobj->headers_out, sobj->buffer,
                sobj->buffer_len, &slider)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02375)
                    "out-headers didn't fit in buffer: %s", sobj->name);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }
    }

    /* Parse the vary header and dump those fields from the headers_in. */
    /* TODO: Make call to the same thing cache_select calls to crack Vary. */
    if (sobj->headers_in) {
        if (APR_SUCCESS != store_table(sobj->headers_in, sobj->buffer,
                sobj->buffer_len, &slider)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(02376)
                    "in-headers didn't fit in buffer %s",
                    sobj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }
    }

    sobj->body_offset = slider;

    return APR_SUCCESS;
}