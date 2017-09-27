        }

        /* See the Kludge in includes_filter for why.
         * Basically, it puts a bread crumb in here, then looks
         * for the crumb later to see if its been here.
         */
        if (rr) {
            ap_set_module_config(rr->request_config, &include_module, r);
        }

        if (!error_fmt && ap_run_sub_req(rr)) {
            error_fmt = "unable to include \"%s\" in parsed file %s";
        }

        if (error_fmt) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error_fmt, tag_val,
                    r->filename);
            if (last_error) {
                /* onerror threw an error, give up completely */
                break;
            }
            last_error = error_fmt;
        }
        else {
            last_error = NULL;
        }

        /* Do *not* destroy the subrequest here; it may have allocated
         * variables in this r->subprocess_env in the subrequest's
         * r->pool, so that pool must survive as long as this request.
         * Yes, this is a memory leak. */

    }

    if (last_error) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
    }

    return APR_SUCCESS;
}

/*
 * <!--#echo [decoding="..."] [encoding="..."] var="..." [decoding="..."]
 *  [encoding="..."] var="..." ... -->
 */
static apr_status_t handle_echo(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    const char *encoding = "entity", *decoding = "none";
    request_rec *r = f->r;
    int error = 0;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, APLOGNO(01343)
                      "missing argument for echo element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
