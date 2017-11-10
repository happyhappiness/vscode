static const char *set_keep_alive(cmd_parms *cmd, void *dummy,
                                  int arg)
{
    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    if (err != NULL) {
        return err;
    }

    cmd->server->keep_alive = arg;
    return NULL;
}