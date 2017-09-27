            if (eos) {
                /* should not occur, because we have an APR timeout in place */
                AP_DEBUG_ASSERT(1 != 1);
            }
            return APR_SUCCESS;
        }
        
        if (rv == APR_SUCCESS) {
            bb = apr_brigade_create(r->pool, c->bucket_alloc);
            b = apr_bucket_transient_create(buf, len, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "ap_pass_brigade(filtered buffer) failed");
                return rv;
            }
        }
    } while (rv == APR_SUCCESS);

    if (!APR_STATUS_IS_EOF(rv)) {
        return rv;
    }

    if (eos) {
        /* pass down eos */
        bb = apr_brigade_create(r->pool, c->bucket_alloc);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "ap_pass_brigade(eos) failed");
            return rv;
        }
    }

    return APR_SUCCESS;
}

#if 0
static int ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb, 
                           ap_input_mode_t mode, apr_read_type_e block,
                           apr_off_t readbytes)
{
    apr_status_t rv;
    apr_bucket *b;
    char *buf;
    apr_ssize_t len;
    char *zero;

    rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    APR_BRIGADE_FOREACH(b, bb) {
        if (!APR_BUCKET_IS_EOS(b)) {
            if ((rv = apr_bucket_read(b, (const char **)&buf, &len, APR_BLOCK_READ)) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "apr_bucket_read() failed");
                return rv;
            }
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "apr_bucket_read -> %d bytes",
                         len);
            while ((zero = memchr(buf, '0', len))) {
                *zero = 'a';
            }
        }
        else
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "got eos bucket");
    }

    return rv;
}
#endif

module AP_MODULE_DECLARE_DATA ext_filter_module =
{
    STANDARD20_MODULE_STUFF,
    create_ef_dir_conf,
    merge_ef_dir_conf,
