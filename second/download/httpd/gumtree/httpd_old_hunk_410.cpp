     * the output filters are invoked by the default handler.
     */
    if ((errstatus = ap_discard_request_body(r)) != OK) {
        return errstatus;
    }

    if (r->method_number != M_GET && r->method_number != M_POST) {
        if (r->method_number == M_INVALID) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Invalid method in request %s", r->the_request);
            return HTTP_NOT_IMPLEMENTED;
        }

        if (r->method_number == M_OPTIONS) {
            return ap_send_http_options(r);
        }
        return HTTP_METHOD_NOT_ALLOWED;
    }

    if (r->finfo.filetype == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r,
                      "File does not exist: %s", r->filename);
        return HTTP_NOT_FOUND;
    }

    if ((r->used_path_info != AP_REQ_ACCEPT_PATH_INFO) &&
        r->path_info && *r->path_info)
    {
        /* default to reject */
        ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r,
                      "File does not exist: %s",
                      apr_pstrcat(r->pool, r->filename, r->path_info, NULL));
        return HTTP_NOT_FOUND;
    }

    if ((status = apr_file_open(&fd, r->filename, APR_READ | APR_BINARY, 0,
                                r->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "file permissions deny server access: %s", r->filename);
        return HTTP_FORBIDDEN;
    }

    ap_update_mtime(r, r->finfo.mtime);
    ap_set_last_modified(r);
    ap_set_etag(r);
    apr_table_setn(r->headers_out, "Accept-Ranges", "bytes");
    ap_set_content_length(r, r->finfo.size);
    if ((errstatus = ap_meets_conditions(r)) != OK) {
        apr_file_close(fd);
        return errstatus;
    }

    if (bld_content_md5) {
        apr_table_setn(r->headers_out, "Content-MD5",
                       ap_md5digest(r->pool, fd));
    }

    bb = apr_brigade_create(r->pool, c->bucket_alloc);
#if APR_HAS_LARGE_FILES
    if (r->finfo.size > AP_MAX_SENDFILE) {
        /* APR_HAS_LARGE_FILES issue; must split into mutiple buckets,
         * no greater than MAX(apr_size_t), and more granular than that
         * in case the brigade code/filters attempt to read it directly.
         */
        apr_off_t fsize = r->finfo.size;
        e = apr_bucket_file_create(fd, 0, AP_MAX_SENDFILE, r->pool,
                                   c->bucket_alloc);
        while (fsize > AP_MAX_SENDFILE) {
            apr_bucket *ce;
            apr_bucket_copy(e, &ce);
            APR_BRIGADE_INSERT_TAIL(bb, ce);
            e->start += AP_MAX_SENDFILE;
            fsize -= AP_MAX_SENDFILE;
        }
        e->length = (apr_size_t)fsize; /* Resize just the last bucket */
    }
    else
#endif
        e = apr_bucket_file_create(fd, 0, (apr_size_t)r->finfo.size,
                                   r->pool, c->bucket_alloc);

    APR_BRIGADE_INSERT_TAIL(bb, e);
    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);

    return ap_pass_brigade(r->output_filters, bb);

}

static int net_time_filter(ap_filter_t *f, apr_bucket_brigade *b,
                           ap_input_mode_t mode, apr_read_type_e block,
                           apr_off_t readbytes)
{
