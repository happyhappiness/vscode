            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "File does not exist: %s",
                          apr_pstrcat(r->pool, r->filename, r->path_info, NULL));
            return HTTP_NOT_FOUND;
        }

        /* We understood the (non-GET) method, but it might not be legal for
           this particular resource. Check to see if the 'deliver_script'
           flag is set. If so, then we go ahead and deliver the file since
           it isn't really content (only GET normally returns content).

           Note: based on logic further above, the only possible non-GET
           method at this point is POST. In the future, we should enable
           script delivery for all methods.  */
        if (r->method_number != M_GET) {
            core_request_config *req_cfg;

            req_cfg = ap_get_module_config(r->request_config, &core_module);
            if (!req_cfg->deliver_script) {
                /* The flag hasn't been set for this request. Punt. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "This resource does not accept the %s method.",
                              r->method);
                return HTTP_METHOD_NOT_ALLOWED;
            }
        }


        if ((status = apr_file_open(&fd, r->filename, APR_READ | APR_BINARY
#if APR_HAS_SENDFILE
                            | ((d->enable_sendfile == ENABLE_SENDFILE_OFF) 
                                                ? 0 : APR_SENDFILE_ENABLED)
#endif
                                    , 0, r->pool)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                          "file permissions deny server access: %s", r->filename);
            return HTTP_FORBIDDEN;
        }

        ap_update_mtime(r, r->finfo.mtime);
