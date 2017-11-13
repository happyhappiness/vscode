static apr_status_t store_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);
    apr_status_t rv;
    apr_size_t amt;
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;

    disk_cache_info_t disk_info;
    struct iovec iov[2];

    /* This is flaky... we need to manage the cache_info differently */
    h->cache_obj->info = *info;

    if (r->headers_out) {
        const char *tmp;

        tmp = apr_table_get(r->headers_out, "Vary");

        if (tmp) {
            apr_array_header_t* varray;
            apr_uint32_t format = VARY_FORMAT_VERSION;

            /* If we were initially opened as a vary format, rollback
             * that internal state for the moment so we can recreate the
             * vary format hints in the appropriate directory.
             */
            if (dobj->prefix) {
                dobj->hdrsfile = dobj->prefix;
                dobj->prefix = NULL;
            }

            mkdir_structure(conf, dobj->hdrsfile, r->pool);

            rv = apr_file_mktemp(&dobj->tfd, dobj->tempfile,
                                 APR_CREATE | APR_WRITE | APR_BINARY | APR_EXCL,
                                 r->pool);

            if (rv != APR_SUCCESS) {
                return rv;
            }

            amt = sizeof(format);
            apr_file_write(dobj->tfd, &format, &amt);

            amt = sizeof(info->expire);
            apr_file_write(dobj->tfd, &info->expire, &amt);

            varray = apr_array_make(r->pool, 6, sizeof(char*));
            tokens_to_array(r->pool, tmp, varray);

            store_array(dobj->tfd, varray);

            apr_file_close(dobj->tfd);

            dobj->tfd = NULL;

            rv = safe_file_rename(conf, dobj->tempfile, dobj->hdrsfile,
                                  r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                    "disk_cache: rename tempfile to varyfile failed: %s -> %s",
                    dobj->tempfile, dobj->hdrsfile);
                return rv;
            }

            dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);
            tmp = regen_key(r->pool, r->headers_in, varray, dobj->name);
            dobj->prefix = dobj->hdrsfile;
            dobj->hashfile = NULL;
            dobj->datafile = data_file(r->pool, conf, dobj, tmp);
            dobj->hdrsfile = header_file(r->pool, conf, dobj, tmp);
        }
    }


    rv = apr_file_mktemp(&dobj->hfd, dobj->tempfile,
                         APR_CREATE | APR_WRITE | APR_BINARY |
                         APR_BUFFERED | APR_EXCL, r->pool);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    disk_info.format = DISK_FORMAT_VERSION;
    disk_info.date = info->date;
    disk_info.expire = info->expire;
    disk_info.entity_version = dobj->disk_info.entity_version++;
    disk_info.request_time = info->request_time;
    disk_info.response_time = info->response_time;
    disk_info.status = info->status;

    disk_info.name_len = strlen(dobj->name);

    iov[0].iov_base = (void*)&disk_info;
    iov[0].iov_len = sizeof(disk_cache_info_t);
    iov[1].iov_base = (void*)dobj->name;
    iov[1].iov_len = disk_info.name_len;

    rv = apr_file_writev(dobj->hfd, (const struct iovec *) &iov, 2, &amt);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (r->headers_out) {
        apr_table_t *headers_out;

        headers_out = ap_cache_cacheable_hdrs_out(r->pool, r->headers_out,
                                                  r->server);

        if (!apr_table_get(headers_out, "Content-Type")
            && r->content_type) {
            apr_table_setn(headers_out, "Content-Type",
                           ap_make_content_type(r, r->content_type));
        }

        headers_out = apr_table_overlay(r->pool, headers_out,
                                        r->err_headers_out);
        rv = store_table(dobj->hfd, headers_out);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    /* Parse the vary header and dump those fields from the headers_in. */
    /* FIXME: Make call to the same thing cache_select calls to crack Vary. */
    if (r->headers_in) {
        apr_table_t *headers_in;

        headers_in = ap_cache_cacheable_hdrs_out(r->pool, r->headers_in,
                                                 r->server);
        rv = store_table(dobj->hfd, headers_in);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    apr_file_close(dobj->hfd); /* flush and close */

    /* Remove old file with the same name. If remove fails, then
     * perhaps we need to create the directory tree where we are
     * about to write the new headers file.
     */
    rv = apr_file_remove(dobj->hdrsfile, r->pool);
    if (rv != APR_SUCCESS) {
        mkdir_structure(conf, dobj->hdrsfile, r->pool);
    }

    rv = safe_file_rename(conf, dobj->tempfile, dobj->hdrsfile, r->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "disk_cache: rename tempfile to hdrsfile failed: %s -> %s",
                     dobj->tempfile, dobj->hdrsfile);
        return rv;
    }

    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "disk_cache: Stored headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}