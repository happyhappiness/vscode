static const char *dbd_init_sql(cmd_parms *cmd, void *dconf, const char *query)
{
    if (!query || *query == '\n') {
        return "You should specify SQL statement";
    }

    ap_dbd_sql_init(cmd->server, query);

    return NULL;
}