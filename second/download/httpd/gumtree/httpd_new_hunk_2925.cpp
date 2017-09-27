                        char *replaced = ap_pregsub(r->pool, elts[j].val, val,
                                                    AP_MAX_REG_MATCH, regm);
                        if (replaced) {
                            apr_table_setn(r->subprocess_env, elts[j].key,
                                           replaced);
                        }
                        else {
                            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01505)
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
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "Setting %s",
                              elts[j].key);
            }
        }
    }

    return DECLINED;
}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_header_parser(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(setenvif) =
{
    STANDARD20_MODULE_STUFF,
    create_setenvif_config_dir, /* dir config creater */
