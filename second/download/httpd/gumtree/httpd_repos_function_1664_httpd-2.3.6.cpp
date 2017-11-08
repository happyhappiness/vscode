static const char *add_cluster(cmd_parms *cmd, void *d,
                               int argc, char *const argv[])
{
    const char *rv;
    ap_serf_cluster_provider_t *backend;
    int i;
    serf_cluster_t *cluster = NULL;
    serf_server_config_t *ctx = 
        (serf_server_config_t *)ap_get_module_config(cmd->server->module_config,
                                                     &serf_module);

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
  
    if (err != NULL) {
        return err;
    }

    if (argc < 2) {
        return "SerfCluster must have at least a name and provider.";
    }
    
    cluster = apr_palloc(cmd->pool, sizeof(serf_cluster_t));
    cluster->name = apr_pstrdup(cmd->pool, argv[0]);
    cluster->provider = apr_pstrdup(cmd->pool, argv[1]);
    cluster->params = apr_table_make(cmd->pool, 6);

    backend = ap_lookup_provider(AP_SERF_CLUSTER_PROVIDER, cluster->provider, "0");
    
    if (backend == NULL) {
        return apr_psprintf(cmd->pool, "SerfCluster: unable to find "
                            "provider '%s'", cluster->provider);
    }

    for (i = 2; i < argc; i++) {
        const char *p = argv[i];
        const char *x = ap_strchr_c(p, '=');

        if (x && strlen(p) > 1) {
            apr_table_addn(cluster->params,
                           apr_pstrndup(cmd->pool, p, x-p),
                           x+1);
        }
        else {
            apr_table_addn(cluster->params, 
                           apr_pstrdup(cmd->pool, p),
                           "");
        }
    }

    if (backend->check_config == NULL) {
        return apr_psprintf(cmd->pool, "SerfCluster: Provider '%s' failed to "
                             "provider a configuration checker",
                            cluster->provider);
    }

    rv = backend->check_config(backend->baton, cmd, cluster->params);
    
    if (rv) {
        return rv;
    }

    apr_hash_set(ctx->clusters, cluster->name, APR_HASH_KEY_STRING, cluster);

    return NULL;
}