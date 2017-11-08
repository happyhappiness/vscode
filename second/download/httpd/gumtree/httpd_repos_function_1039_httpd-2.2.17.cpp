static const char *dbd_prepare(cmd_parms *cmd, void *dconf, const char *query,
                               const char *label)
{
    if (!label) {
        label = query;
        query = "";
    }

    ap_dbd_prepare(cmd->server, query, label);

    return NULL;
}