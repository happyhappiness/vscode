static const char *set_timeout(cmd_parms *cmd, void *d_, const char *arg)
{
    ident_config_rec *d = d_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (!err) {
        d->timeout = apr_time_from_sec(atoi(arg));
        d->timeout_unset = 0;
    }

    return err;
}