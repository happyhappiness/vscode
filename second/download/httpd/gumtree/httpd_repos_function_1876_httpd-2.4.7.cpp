static const char *cmd_hm_listen(cmd_parms *cmd,
                                 void *dconf, const char *mcast_addr)
{
    apr_status_t rv;
    char *host_str;
    char *scope_id;
    apr_port_t port = 0;
    apr_pool_t *p = cmd->pool;
    hm_ctx_t *ctx =
        (hm_ctx_t *) ap_get_module_config(cmd->server->module_config,
                                          &heartmonitor_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (!ctx->active) {
        ctx->active = 1;
    }
    else {
        return "HeartbeatListen: May only be specified once.";
    }

    rv = apr_parse_addr_port(&host_str, &scope_id, &port, mcast_addr, cmd->temp_pool);

    if (rv) {
        return "HeartbeatListen: Unable to parse multicast address.";
    }

    if (host_str == NULL) {
        return "HeartbeatListen: No host provided in multicast address";
    }

    if (port == 0) {
        return "HeartbeatListen: No port provided in multicast address";
    }

    rv = apr_sockaddr_info_get(&ctx->mcast_addr, host_str, APR_INET, port, 0,
                               p);

    if (rv) {
        return
            "HeartbeatListen: apr_sockaddr_info_get failed on multicast address";
    }

    return NULL;
}