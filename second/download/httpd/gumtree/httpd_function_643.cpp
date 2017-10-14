static apr_status_t handle_include(include_ctx_t *ctx, ap_filter_t *f,
                                   apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for include element in %s",
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
        char *tag     = NULL;
        char *tag_val = NULL;
        request_rec *rr = NULL;
        char *error_fmt = NULL;
        char *parsed_string;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        if (strcmp(tag, "virtual") && strcmp(tag, "file")) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" to tag include in %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }

        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                            SSI_EXPAND_DROP_NAME);
        if (tag[0] == 'f') {
            char *newpath;
            apr_status_t rv;

            /* be safe; only files in this directory or below allowed */
            rv = apr_filepath_merge(&newpath, NULL, parsed_string,
                                    APR_FILEPATH_NOTABOVEROOT |
                                    APR_FILEPATH_SECUREROOTTEST |
                                    APR_FILEPATH_NOTABSOLUTE, ctx->dpool);

            if (rv != APR_SUCCESS) {
                error_fmt = "unable to include file \"%s\" in parsed file %s";
            }
            else {
                rr = ap_sub_req_lookup_file(newpath, r, f->next);
            }
        }
        else {
            rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
        }

        if (!error_fmt && rr->status != HTTP_OK) {
            error_fmt = "unable to include \"%s\" in parsed file %s";
        }

        if (!error_fmt && (ctx->flags & SSI_FLAG_NO_EXEC) &&
            rr->content_type && strncmp(rr->content_type, "text/", 5)) {

            error_fmt = "unable to include potential exec \"%s\" in parsed "
                        "file %s";
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
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        }

        /* Do *not* destroy the subrequest here; it may have allocated
         * variables in this r->subprocess_env in the subrequest's
         * r->pool, so that pool must survive as long as this request.
         * Yes, this is a memory leak. */

        if (error_fmt) {
            break;
        }
    }

    return APR_SUCCESS;
}