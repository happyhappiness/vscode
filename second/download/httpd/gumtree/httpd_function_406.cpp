static apr_status_t store_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);
    apr_status_t rv;
    apr_size_t amt;
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;
    apr_file_t *hfd = dobj->hfd;

    if (!hfd)  {
        disk_cache_info_t disk_info;
        struct iovec iov[2];

        if (!dobj->hdrsfile) {
            dobj->hdrsfile = header_file(r->pool, conf, dobj,
                                         h->cache_obj->key);
        }

        /* This is flaky... we need to manage the cache_info differently */
        h->cache_obj->info = *info;

        /* Remove old file with the same name. If remove fails, then
         * perhaps we need to create the directory tree where we are
         * about to write the new headers file.
         */
        rv = apr_file_remove(dobj->hdrsfile, r->pool);
        if (rv != APR_SUCCESS) {
            mkdir_structure(conf, dobj->hdrsfile, r->pool);
        }

        rv = apr_file_open(&dobj->hfd, dobj->hdrsfile,
                           APR_WRITE | APR_CREATE | APR_EXCL,
                           APR_OS_DEFAULT, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        hfd = dobj->hfd;
        dobj->name = h->cache_obj->key;

        disk_info.format = DISK_FORMAT_VERSION;
        disk_info.date = info->date;
        disk_info.expire = info->expire;
        disk_info.entity_version = dobj->disk_info.entity_version++;
        disk_info.request_time = info->request_time;
        disk_info.response_time = info->response_time;

        disk_info.name_len = strlen(dobj->name);
        disk_info.status = r->status;

        /* This case only occurs when the content is generated locally */
        if (!r->status_line) {
            r->status_line = ap_get_status_line(r->status);
        }

        iov[0].iov_base = (void*)&disk_info;
        iov[0].iov_len = sizeof(disk_cache_info_t);
        iov[1].iov_base = dobj->name;
        iov[1].iov_len = disk_info.name_len;

        rv = apr_file_writev(hfd, (const struct iovec *) &iov, 2, &amt);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        if (r->headers_out) {
            apr_table_t *headers_out;

            headers_out = ap_cache_cacheable_hdrs_out(r->pool, r->headers_out);

            rv = store_table(hfd, headers_out);
            if (rv != APR_SUCCESS) {
                return rv;
            }

            /* This case only occurs when the content is generated locally */
            if (!apr_table_get(r->headers_out, "Content-Type") && r->content_type) {
                apr_table_setn(r->headers_out, "Content-Type",
                               ap_make_content_type(r, r->content_type));
            }
        }

        /* Parse the vary header and dump those fields from the headers_in. */
        /* Make call to the same thing cache_select_url calls to crack Vary. */
        /* @@@ Some day, not today. */
        if (r->headers_in) {
            rv = store_table(hfd, r->headers_in);
            if (rv != APR_SUCCESS) {
                return rv;
            }
        }
        apr_file_close(hfd); /* flush and close */
    }
    else {
        /* XXX log message */
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "disk_cache: Stored headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}