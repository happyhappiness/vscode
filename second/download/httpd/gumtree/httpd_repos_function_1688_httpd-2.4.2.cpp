static const char *cmd_hb_address(cmd_parms *cmd,
                                  void *dconf, const char *addr)
{
    apr_status_t rv;
    char *host_str;
    char *scope_id;
    apr_port_t port = 0;
    apr_pool_t *p = cmd->pool;
    hb_ctx_t *ctx =
        (hb_ctx_t *) ap_get_module_config(cmd->server->module_config,
                                          &heartbeat_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (!ctx->active) {
        ctx->active = 1;
    }
    else {
        return "HeartbeatAddress: May only be specified once.";
    }

    rv = apr_parse_addr_port(&host_str, &scope_id, &port, addr, cmd->temp_pool);

    if (rv) {
        return "HeartbeatAddress: Unable to parse address.";
    }

    if (host_str == NULL) {
        return "HeartbeatAddress: No host provided in address";
    }

    if (port == 0) {
        return "HeartbeatAddress: No port provided in address";
    }

    rv = apr_sockaddr_info_get(&ctx->mcast_addr, host_str, APR_INET, port, 0,
                               p);

    if (rv) {
        return "HeartbeatAddress: apr_sockaddr_info_get failed.";
    }

    return NULL;
}