            if (eos) {
                /* should not occur, because we have an APR timeout in place */
                AP_DEBUG_ASSERT(1 != 1);
            }
            return APR_SUCCESS;
        }

        if (rv == APR_SUCCESS) {
            b = apr_bucket_heap_create(buf, len, NULL, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }
    } while (rv == APR_SUCCESS);

    if (!APR_STATUS_IS_EOF(rv)) {
        return rv;
    }

    if (eos) {
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
    }

    return APR_SUCCESS;
}

static apr_status_t ef_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    if (!ctx) {
        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
            return rv;
        }
        ctx = f->ctx;
    }
    if (ctx->noop) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    rv = ef_unified_filter(f, bb);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "ef_unified_filter() failed");
    }

    if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "ap_pass_brigade() failed");
    }
    return rv;
}

static int ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb,
                           ap_input_mode_t mode, apr_read_type_e block,
                           apr_off_t readbytes)
{
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    if (!ctx) {
        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
            return rv;
        }
        ctx = f->ctx;
    }

    if (ctx->noop) {
        ap_remove_input_filter(f);
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = ef_unified_filter(f, bb);
    return rv;
}

module AP_MODULE_DECLARE_DATA ext_filter_module =
{
    STANDARD20_MODULE_STUFF,
    create_ef_dir_conf,
    merge_ef_dir_conf,
