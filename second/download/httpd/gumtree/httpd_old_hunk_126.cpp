                
                if (ctx->flags & FLAG_COND_TRUE) {
                    ctx->flags &= FLAG_CLEAR_PRINTING;
                    return (0);
                }
                if (expr == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                  "missing expr in elif statement: %s", 
                                  r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return (1);
                }
