static const char *
    add_pass(cmd_parms *cmd, void *dummy, const char *f, const char *r)
{
    server_rec *s = cmd->server;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(s->module_config, &proxy_module);
    struct proxy_alias *new;
    if (r!=NULL && cmd->path == NULL ) {
        new = apr_array_push(conf->aliases);
        new->fake = f;
        new->real = r;
    } else if (r==NULL && cmd->path != NULL) {
        new = apr_array_push(conf->aliases);
        new->fake = cmd->path;
        new->real = f;
    } else {
        if ( r== NULL)
            return "ProxyPass needs a path when not defined in a location";
        else 
            return "ProxyPass can not have a path when defined in a location";
    }

     return NULL;
}