        int i;
        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);

        /* Initialize shared scoreboard data */
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            if (balancer->lbmethod && balancer->lbmethod->reset)
               balancer->lbmethod->reset(balancer, s);
            init_balancer_members(conf, s, balancer);
            balancer++;
        }
        s = s->next;
    }

}

static const char *set_balancer_nonce (cmd_parms *cmd, void *dummy, const char *arg,
                                       const char *val)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (!strcasecmp(arg, "None")) {
        *balancer_nonce = '\0';
    } else if (!strcasecmp(arg, "Set")) {
        if (val) {
            apr_cpystrn(balancer_nonce, val, sizeof(balancer_nonce));
        } else {
            return "BalancerNonce Set requires an argument";
        }
    } else if (strcasecmp(arg, "Default")) {
        return "Bad argument for BalancerNonce: Must be 'Set', 'None' or 'Default'";
    }
    return NULL;
}

static const command_rec balancer_cmds[] =
{
    AP_INIT_TAKE12("BalancerNonce", set_balancer_nonce, NULL,
       RSRC_CONF, "Set value for balancer-manager nonce"),
    {NULL}
};

static void ap_proxy_balancer_register_hook(apr_pool_t *p)
{
    /* Only the mpm_winnt has child init hook handler.
     * make sure that we are called after the mpm
     * initializes
     */
    static const char *const aszPred[] = { "mpm_winnt.c", NULL};
     /* manager handler */
    ap_hook_post_config(balancer_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(balancer_handler, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_child_init(child_init, aszPred, NULL, APR_HOOK_MIDDLE);
    proxy_hook_pre_request(proxy_balancer_pre_request, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_post_request(proxy_balancer_post_request, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_balancer_canon, NULL, NULL, APR_HOOK_FIRST);
}

AP_DECLARE_MODULE(proxy_balancer) = {
    STANDARD20_MODULE_STUFF,
    NULL,       /* create per-directory config structure */
    NULL,       /* merge per-directory config structures */
    NULL,       /* create per-server config structure */
    NULL,       /* merge per-server config structures */
    balancer_cmds,       /* command apr_table_t */
    ap_proxy_balancer_register_hook /* register hooks */
};
