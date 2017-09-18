                rv = (*handle_func)(ctx, bb, r, f, dptr, &content_head);
                if ((rv != 0) && (rv != 1)) {
                    return (rv);
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                              "unknown directive \"%s\" in parsed doc %s",
                              ctx->combined_tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_bkt, dptr, content_head);
            }

            /* This chunk of code starts at the first bucket in the chain
