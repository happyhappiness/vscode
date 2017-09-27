                        char *replaced = ap_pregsub(r->pool, elts[j].val, val,
                                                    AP_MAX_REG_MATCH, regm);
                        if (replaced) {
                            apr_table_setn(r->subprocess_env, elts[j].key,
                                           replaced);
                        }
                        else {
                            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                                          "Regular expression replacement "
                                          "failed for '%s', value too long?",
                                          elts[j].key);
                            return HTTP_INTERNAL_SERVER_ERROR;
                        }
                    }
                    else {
                        apr_table_setn(r->subprocess_env, elts[j].key,
                                       elts[j].val);
                    }
                }
