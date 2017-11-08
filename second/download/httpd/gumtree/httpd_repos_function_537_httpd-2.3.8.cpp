static const char *set_idcheck(cmd_parms *cmd, void *d_, int arg)
{
    ident_config_rec *d = d_;

    d->do_rfc1413 = arg ? 1 : 0;
    return NULL;
}