static const char *set_default_start_tag(cmd_parms *cmd, void *mconfig, const char *msg)
{
    include_server_config *conf;
    conf= ap_get_module_config(cmd->server->module_config , &include_module);
    conf->default_start_tag = apr_pstrdup(cmd->pool, msg);
    conf->start_tag_len = strlen(conf->default_start_tag );
    bndm_compile(&conf->start_seq_pat, conf->default_start_tag, 
                 conf->start_tag_len); 

    return NULL;
}