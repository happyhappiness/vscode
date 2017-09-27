                            }
                            if (uri.fragment) {
                                found = apr_pstrcat(r->pool, found, "#",
                                                    uri.fragment, NULL);
                            }
                       }
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00672)
                                      "Regex substitution in '%s' failed. "
                                      "Replacement too long?", alias->real);
                        return PREGSUB_ERROR;
