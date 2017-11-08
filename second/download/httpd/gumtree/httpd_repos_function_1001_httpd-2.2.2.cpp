static const char *dbd_prepare(cmd_parms *cmd, void *cfg, const char *query,
                               const char *label)
{
    ap_dbd_prepare(cmd->server, query, label);
    return NULL;
}