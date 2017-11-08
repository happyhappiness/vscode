static apr_status_t write_headers(cache_handle_t *h, request_rec *r)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &cache_disk_module);
    apr_status_t rv;
    apr_size_t amt;
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;

    disk_cache_info_t disk_info;
    struct iovec iov[2];

    memset(&disk_info, 0, sizeof(disk_cache_info_t));

    if (dobj->headers_out) {
        const char *tmp;

        tmp = apr_table_get(dobj->headers_out, "Vary");

        if (tmp) {
            apr_array_header_t* varray;
            apr_uint32_t format = VARY_FORMAT_VERSION;

            /* If we were initially opened as a vary format, rollback
             * that internal state for the moment so we can recreate the
             * vary format hints in the appropriate directory.
             */
            if (dobj->prefix) {
                dobj->hdrs.file = dobj->prefix;
                dobj->prefix = NULL;
            }

            rv = mkdir_structure(conf, dobj->hdrs.file, r->pool);

            rv = apr_file_mktemp(&dobj->vary.tempfd, dobj->vary.tempfile,
                                 APR_CREATE | APR_WRITE | APR_BINARY | APR_EXCL,
                                 dobj->vary.pool);

            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00721)
                        "could not create vary file %s",
                        dobj->vary.tempfile);
                return rv;
            }

            amt = sizeof(format);
            rv = apr_file_write(dobj->vary.tempfd, &format, &amt);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00722)
                        "could not write to vary file %s",
                        dobj->vary.tempfile);
                apr_file_close(dobj->vary.tempfd);
                apr_pool_destroy(dobj->vary.pool);
                return rv;
            }

            amt = sizeof(h->cache_obj->info.expire);
            rv = apr_file_write(dobj->vary.tempfd, &h->cache_obj->info.expire,
                    &amt);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00723)
                        "could not write to vary file %s",
                        dobj->vary.tempfile);
                apr_file_close(dobj->vary.tempfd);
                apr_pool_destroy(dobj->vary.pool);
                return rv;
            }

            varray = apr_array_make(r->pool, 6, sizeof(char*));
            tokens_to_array(r->pool, tmp, varray);

            store_array(dobj->vary.tempfd, varray);

            rv = apr_file_close(dobj->vary.tempfd);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00724)
                        "could not close vary file %s",
                        dobj->vary.tempfile);
                apr_pool_destroy(dobj->vary.pool);
                return rv;
            }

            tmp = regen_key(r->pool, dobj->headers_in, varray, dobj->name);
            dobj->prefix = dobj->hdrs.file;
            dobj->hashfile = NULL;
            dobj->data.file = data_file(r->pool, conf, dobj, tmp);
            dobj->hdrs.file = header_file(r->pool, conf, dobj, tmp);
        }
    }


    rv = apr_file_mktemp(&dobj->hdrs.tempfd, dobj->hdrs.tempfile,
                         APR_CREATE | APR_WRITE | APR_BINARY |
                         APR_BUFFERED | APR_EXCL, dobj->hdrs.pool);

    if (rv != APR_SUCCESS) {
       ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00725)
                "could not create header file %s",
                dobj->hdrs.tempfile);
        return rv;
    }

    disk_info.format = DISK_FORMAT_VERSION;
    disk_info.date = h->cache_obj->info.date;
    disk_info.expire = h->cache_obj->info.expire;
    disk_info.entity_version = dobj->disk_info.entity_version++;
    disk_info.request_time = h->cache_obj->info.request_time;
    disk_info.response_time = h->cache_obj->info.response_time;
    disk_info.status = h->cache_obj->info.status;
    disk_info.inode = dobj->disk_info.inode;
    disk_info.device = dobj->disk_info.device;
    disk_info.has_body = dobj->disk_info.has_body;
    disk_info.header_only = dobj->disk_info.header_only;

    disk_info.name_len = strlen(dobj->name);

    memcpy(&disk_info.control, &h->cache_obj->info.control, sizeof(cache_control_t));

    iov[0].iov_base = (void*)&disk_info;
    iov[0].iov_len = sizeof(disk_cache_info_t);
    iov[1].iov_base = (void*)dobj->name;
    iov[1].iov_len = disk_info.name_len;

    rv = apr_file_writev(dobj->hdrs.tempfd, (const struct iovec *) &iov, 2, &amt);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00726)
                "could not write info to header file %s",
                dobj->hdrs.tempfile);
        apr_file_close(dobj->hdrs.tempfd);
        apr_pool_destroy(dobj->hdrs.pool);
        return rv;
    }

    if (dobj->headers_out) {
        rv = store_table(dobj->hdrs.tempfd, dobj->headers_out);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00727)
                    "could not write out-headers to header file %s",
                    dobj->hdrs.tempfile);
            apr_file_close(dobj->hdrs.tempfd);
            apr_pool_destroy(dobj->hdrs.pool);
            return rv;
        }
    }

    /* Parse the vary header and dump those fields from the headers_in. */
    /* FIXME: Make call to the same thing cache_select calls to crack Vary. */
    if (dobj->headers_in) {
        rv = store_table(dobj->hdrs.tempfd, dobj->headers_in);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00728)
                    "could not write in-headers to header file %s",
                    dobj->hdrs.tempfile);
            apr_file_close(dobj->hdrs.tempfd);
            apr_pool_destroy(dobj->hdrs.pool);
            return rv;
        }
    }

    rv = apr_file_close(dobj->hdrs.tempfd); /* flush and close */
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00729)
                "could not close header file %s",
                dobj->hdrs.tempfile);
        apr_pool_destroy(dobj->hdrs.pool);
        return rv;
    }

    return APR_SUCCESS;
}