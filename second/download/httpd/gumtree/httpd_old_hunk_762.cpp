        return proxy_ssl_disable(c);
    }

    return 0;
}

static int proxy_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    proxy_ssl_enable = APR_RETRIEVE_OPTIONAL_FN(ssl_proxy_enable);
    proxy_ssl_disable = APR_RETRIEVE_OPTIONAL_FN(ssl_engine_disable);

    return OK;
}

static void register_hooks(apr_pool_t *p)
{
    /* fixup before mod_rewrite, so that the proxied url will not
     * escaped accidentally by our fixup.
     */
    static const char * const aszSucc[]={ "mod_rewrite.c", NULL };

    /* handler */
    ap_hook_handler(proxy_handler, NULL, NULL, APR_HOOK_FIRST);
    /* filename-to-URI translation */
    ap_hook_translate_name(proxy_trans, NULL, NULL, APR_HOOK_FIRST);
    /* walk <Proxy > entries and suppress default TRACE behavior */
    ap_hook_map_to_storage(proxy_map_location, NULL,NULL, APR_HOOK_FIRST);
    /* fixups */
    ap_hook_fixups(proxy_fixup, NULL, aszSucc, APR_HOOK_FIRST);
    /* post read_request handling */
    ap_hook_post_read_request(proxy_detect, NULL, NULL, APR_HOOK_FIRST);
    /* post config handling */
    ap_hook_post_config(proxy_post_config, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA proxy_module =
{
    STANDARD20_MODULE_STUFF,
    create_proxy_dir_config,    /* create per-directory config structure */
