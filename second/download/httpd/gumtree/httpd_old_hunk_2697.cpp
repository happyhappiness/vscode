        return APR_SUCCESS;
    }

    ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);

    if (strcmp(tag, "expr")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
                      "to tag if in %s", tag, r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (!expr) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "missing expr value for if "
                      "element in %s", r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    DEBUG_PRINTF((ctx, "****    if expr=\"%s\"\n", expr));

    expr_ret = ap_expr_evalstring(r, expr, &was_error, &ctx->intern->re,
                                  ssi_parse_string, ctx->intern->access_func);

    if (was_error) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

