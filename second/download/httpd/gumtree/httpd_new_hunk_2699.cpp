        return APR_SUCCESS;
    }

    ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);

    if (strcmp(tag, "expr")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01358) "unknown parameter \"%s\" "
                      "to tag if in %s", tag, r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (!expr) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01359) "missing expr in elif "
                      "statement: %s", r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    DEBUG_PRINTF((ctx, "****  elif expr=\"%s\"\n", expr));
