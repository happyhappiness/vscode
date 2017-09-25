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

static apr_status_t store_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b)
{
    apr_bucket *e;
    apr_status_t rv;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);

    if (!dobj->fd) {
        rv = apr_file_open(&dobj->fd, dobj->tempfile,
                           APR_WRITE | APR_CREATE | APR_BINARY| APR_TRUNCATE | APR_BUFFERED,
                           APR_UREAD | APR_UWRITE, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        dobj->file_size = 0;
    }
    for (e = APR_BRIGADE_FIRST(b);
         e != APR_BRIGADE_SENTINEL(b);
         e = APR_BUCKET_NEXT(e))
    {
        const char *str;
        apr_size_t length;
        apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        if (apr_file_write(dobj->fd, str, &length) != APR_SUCCESS) {
          ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: Error when writing cache file for URL %s",
                     h->cache_obj->key);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
        dobj->file_size += length;
        if (dobj->file_size > conf->maxfs) {
          ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check (%lu>%lu)",
                     h->cache_obj->key, (unsigned long)dobj->file_size, (unsigned long)conf->maxfs);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
    }

    /* Was this the final bucket? If yes, close the body file and make sanity checks */
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(b))) {
        if (h->cache_obj->info.len <= 0) {
          /* XXX Fixme: file_size isn't constrained by size_t. */
          h->cache_obj->info.len = dobj->file_size;
        }
        else if (h->cache_obj->info.len != dobj->file_size) {
          /* "Content-Length" and actual content disagree in size. Log that. */
          ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "disk_cache: URL %s failed the size check (%lu != %lu)",
                       h->cache_obj->key,
                       (unsigned long)h->cache_obj->info.len,
                       (unsigned long)dobj->file_size);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
        if (dobj->file_size < conf->minfs) {
          ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check (%lu<%lu)",
                     h->cache_obj->key, (unsigned long)dobj->file_size, (unsigned long)conf->minfs);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
        /* All checks were fine. Move tempfile to final destination */
        file_cache_el_final(h, r);    /* Link to the perm file, and close the descriptor */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: Body for URL %s cached.",  dobj->name);
    }

    return APR_SUCCESS;
}
