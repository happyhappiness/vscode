    }

    while (1) {
        char *tag = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);

        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "var")) {
            var = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                      SSI_EXPAND_DROP_NAME);
        }
        else if (!strcmp(tag, "value")) {
            char *parsed_string;

            if (!var) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "variable must "
                              "precede value in set directive in %s",
                              r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }

            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);
            apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
                           apr_pstrdup(p, parsed_string));
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Invalid tag for set "
                          "directive in %s", r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

