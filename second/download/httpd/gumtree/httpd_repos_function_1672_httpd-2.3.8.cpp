static const char* hb_config_check(void *baton,
                                   cmd_parms *cmd,
                                   apr_table_t *params)
{
    hb_table_baton_t b;

    if (apr_is_empty_table(params)) {
        return "SerfCluster Heartbeat requires a path to the heartbat information.";
    }
    
    b.p = cmd->pool;
    b.msg = NULL;

    apr_table_do(hb_table_check, &b, params, NULL);
    
    if (b.msg) {
        return b.msg;
    }

    return NULL;
}