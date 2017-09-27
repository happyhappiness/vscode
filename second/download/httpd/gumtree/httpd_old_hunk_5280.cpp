                            }
                            if (uri.fragment) {
                                found = apr_pstrcat(r->pool, found, "#",
                                                    uri.fragment, NULL);
                            }
                       }
                       else {
                           int pathlen = strlen(found) -
                                         (strlen(r->uri + regm[0].rm_eo));
                           AP_DEBUG_ASSERT(pathlen >= 0);
                           AP_DEBUG_ASSERT(pathlen <= strlen(found));
                           ap_set_context_info(r,
                                               apr_pstrmemdup(r->pool, r->uri,
                                                              regm[0].rm_eo),
                                               apr_pstrmemdup(r->pool, found,
                                                              pathlen));
                       }
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00672)
                                      "Regex substitution in '%s' failed. "
                                      "Replacement too long?", alias->real);
                        return PREGSUB_ERROR;
