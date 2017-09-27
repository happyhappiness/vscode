           Note: based on logic further above, the only possible non-GET
           method at this point is POST. In the future, we should enable
           script delivery for all methods.  */
        if (r->method_number != M_GET) {
            core_request_config *req_cfg;

            req_cfg = ap_get_core_module_config(r->request_config);
            if (!req_cfg->deliver_script) {
                /* The flag hasn't been set for this request. Punt. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00131)
                              "This resource does not accept the %s method.",
                              r->method);
                return HTTP_METHOD_NOT_ALLOWED;
            }
        }


        if ((status = apr_file_open(&fd, r->filename, APR_READ | APR_BINARY
#if APR_HAS_SENDFILE
                            | AP_SENDFILE_ENABLED(d->enable_sendfile)
#endif
                                    , 0, r->pool)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00132)
                          "file permissions deny server access: %s", r->filename);
            return HTTP_FORBIDDEN;
        }

        ap_update_mtime(r, r->finfo.mtime);
        ap_set_last_modified(r);
        ap_set_etag(r);
        ap_set_accept_ranges(r);
        ap_set_content_length(r, r->finfo.size);
        if (bld_content_md5) {
            apr_table_setn(r->headers_out, "Content-MD5",
                           ap_md5digest(r->pool, fd));
        }

