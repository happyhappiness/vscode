
            cgi_pfn_ps(ctx, tag_val, parsed_string, sizeof(parsed_string),
                       SSI_EXPAND_LEAVE_NAME);

            rv = include_cmd(ctx, f, bb, parsed_string);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01229) "execution failure "
                              "for parameter \"%s\" to tag exec in file %s",
                              tag, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
