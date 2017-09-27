                          "for %s", r->filename);
            apr_file_close(f);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        bb = apr_brigade_create(r->pool, c->bucket_alloc);
#if APR_HAS_LARGE_FILES
        if (r->finfo.size - pos > AP_MAX_SENDFILE) {
            /* APR_HAS_LARGE_FILES issue; must split into mutiple buckets,
             * no greater than MAX(apr_size_t), and more granular than that
             * in case the brigade code/filters attempt to read it directly.
             */
            apr_off_t fsize = r->finfo.size - pos;
            b = apr_bucket_file_create(f, pos, AP_MAX_SENDFILE,
                                       r->pool, c->bucket_alloc);
            while (fsize > AP_MAX_SENDFILE) {
                APR_BRIGADE_INSERT_TAIL(bb, b);
                apr_bucket_copy(b, &b);
                b->start += AP_MAX_SENDFILE;
                fsize -= AP_MAX_SENDFILE;
            }
            b->length = (apr_size_t)fsize; /* Resize just the last bucket */
        }
        else
#endif
        b = apr_bucket_file_create(f, pos, (apr_size_t) (r->finfo.size - pos),
                                   r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_asis: ap_pass_brigade failed for file %s", r->filename);
            return AP_FILTER_ERROR;
        }
    }
    else {
        apr_file_close(f);
    }

