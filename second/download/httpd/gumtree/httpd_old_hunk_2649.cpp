                        }
                    }
                    else {
                        const char *symbol = output ? "->" : "<-";

                        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                                      0, f->r,
                                      "chk_filter_chain() - can't disable "
                                      "translation %s%s%s; existing "
                                      "translation %s%s%s",
                                      last_xlate_ctx->dc->charset_source,
                                      symbol,
                                      last_xlate_ctx->dc->charset_default,
