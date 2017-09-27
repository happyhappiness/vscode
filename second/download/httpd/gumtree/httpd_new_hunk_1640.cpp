                        char *replaced = ap_pregsub(r->pool, elts[j].val, val,
                                                    AP_MAX_REG_MATCH, regm);
                        if (replaced) {
                            apr_table_setn(r->subprocess_env, elts[j].key,
                                           replaced);
                        }
                    }
                    else {
                        apr_table_setn(r->subprocess_env, elts[j].key,
                                       elts[j].val);
                    }
                }
