const char *ap_set_listener(cmd_parms *cmd, void *dummy, const char *ips)
{
    char *host, *scope_id;
    apr_port_t port;
    apr_status_t rv;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    rv = apr_parse_addr_port(&host, &scope_id, &port, ips, cmd->pool);
    if (rv != APR_SUCCESS) {
        return "Invalid address or port";
    }

    if (host && !strcmp(host, "*")) {
        host = NULL;
    }

    if (scope_id) {
        /* XXX scope id support is useful with link-local IPv6 addresses */
        return "Scope id is not supported";
    }

    if (!port) {
        return "Port must be specified";
    }

    return alloc_listener(cmd->server->process, host, port);
}