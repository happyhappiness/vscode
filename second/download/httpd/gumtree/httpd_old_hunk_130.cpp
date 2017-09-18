            else if (!strcmp(tag, "var")) {
                var = ap_ssi_parse_string(r, ctx, tag_val, NULL,
                                          MAX_STRING_LEN, 0);
            }
            else if (!strcmp(tag, "value")) {
                if (var == (char *) NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                           "variable must precede value in set directive in %s",
                           r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return (-1);
                }
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
                               apr_pstrdup(p, parsed_string));
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "Invalid tag for set directive in %s", r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return -1;
            }
        }
    }
