static const char* static_config_check(void *baton,
                                   cmd_parms *cmd,
                                   apr_table_t *params)
{
    hb_table_baton_t b;
    
    if (apr_is_empty_table(params)) {
        return "SerfCluster Static requires at least a host list.";
    }
    
    b.p = cmd->pool;
    b.msg = NULL;
    
    apr_table_do(static_table_check, &b, params, NULL);
    
    if (b.msg) {
        return b.msg;
    }
    
    if (apr_table_get(params, "hosts") == NULL) {
        return "SerfCluster Static requires at least a hosts parameter";
    }
    return NULL;
}