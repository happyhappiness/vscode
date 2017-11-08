static const char *
    add_pass_reverse(cmd_parms *cmd, void *dconf, const char *f, const char *r)
{
    proxy_dir_conf *conf = dconf;
    struct proxy_alias *new;

    if (r!=NULL && cmd->path == NULL ) {
        new = apr_array_push(conf->raliases);
        new->fake = f;
        new->real = r;
    } else if (r==NULL && cmd->path != NULL) {
        new = apr_array_push(conf->raliases);
        new->fake = cmd->path;
        new->real = f;
    } else {
        if ( r == NULL)
            return "ProxyPassReverse needs a path when not defined in a location";
        else
            return "ProxyPassReverse can not have a path when defined in a location";
    }

    return NULL;
}