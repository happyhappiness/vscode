static const char *socache_mc_set_ttl(cmd_parms *cmd, void *dummy,
                                      const char *arg)
{
    apr_interval_time_t ttl;
    socache_mc_svr_cfg *sconf = ap_get_module_config(cmd->server->module_config,
                                                     &socache_memcache_module);

    if (ap_timeout_parameter_parse(arg, &ttl, "s") != APR_SUCCESS) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           " has wrong format", NULL);
    }

    if ((ttl < apr_time_from_sec(0)) || (ttl > apr_time_from_sec(3600))) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           " can only be 0 or up to one hour.", NULL);
    }

    /* apr_memcache_server_create needs a ttl in usec. */
    sconf->ttl = ttl;

    return NULL;
}