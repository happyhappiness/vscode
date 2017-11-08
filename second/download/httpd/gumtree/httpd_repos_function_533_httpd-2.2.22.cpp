static const char *set_idcheck(cmd_parms *cmd, void *d_, int arg)
{
    ident_config_rec *d = d_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (!err) {
        d->do_rfc1413 = arg ? 1 : 0;
    }

    return err;
}