                ctx->flags |= SSI_FLAG_SIZE_IN_BYTES;
            }
            else if (!strcmp(parsed_string, "abbrev")) {
                ctx->flags &= SSI_FLAG_SIZE_ABBREV;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
                              "\"%s\" to parameter \"sizefmt\" of tag config "
                              "in %s", parsed_string, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" to tag config in %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

