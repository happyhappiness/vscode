static const char *set_allow2f(cmd_parms *cmd, void *d_, const char *arg)
{
    core_dir_config *d = d_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) {
        return err;
    }

    if (0 == strcasecmp(arg, "on")) {
        d->allow_encoded_slashes = 1;
        d->decode_encoded_slashes = 1;
    } else if (0 == strcasecmp(arg, "off")) {
        d->allow_encoded_slashes = 0;
        d->decode_encoded_slashes = 0;
    } else if (0 == strcasecmp(arg, "nodecode")) {
        d->allow_encoded_slashes = 1;
        d->decode_encoded_slashes = 0;
    } else {
        return apr_pstrcat(cmd->pool,
                           cmd->cmd->name, " must be On, Off, or NoDecode",
                           NULL);
    }
    return NULL;
}