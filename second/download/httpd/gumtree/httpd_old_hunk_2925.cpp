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
            }
        }
    }

    return DECLINED;
}

static int setenvif_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                                apr_pool_t *ptemp, server_rec *s)
{
    ssl_ext_list_func = APR_RETRIEVE_OPTIONAL_FN(ssl_ext_list);
    return OK;
}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_header_parser(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
    /* post config handling */
    ap_hook_post_config(setenvif_post_config, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(setenvif) =
{
    STANDARD20_MODULE_STUFF,
    create_setenvif_config_dir, /* dir config creater */
