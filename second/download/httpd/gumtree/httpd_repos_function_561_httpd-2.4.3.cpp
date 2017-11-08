static const char *set_timeout(cmd_parms *cmd, void *d_, const char *arg)
{
    ident_config_rec *d = d_;

    d->timeout = apr_time_from_sec(atoi(arg));
    d->timeout_unset = 0;
    return NULL;
}