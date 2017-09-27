             */
            if (dobj->prefix) {
                dobj->hdrsfile = dobj->prefix;
                dobj->prefix = NULL;
            }

            rv = mkdir_structure(conf, dobj->hdrsfile, r->pool);

            rv = apr_file_mktemp(&dobj->tfd, dobj->tempfile,
                                 APR_CREATE | APR_WRITE | APR_BINARY | APR_EXCL,
                                 r->pool);

            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                    "disk_cache: could not create temp file %s",
                    dobj->tempfile);
                return rv;
            }

            amt = sizeof(format);
            apr_file_write(dobj->tfd, &format, &amt);

