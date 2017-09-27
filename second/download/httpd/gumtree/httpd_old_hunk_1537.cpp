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

