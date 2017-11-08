static const char *set_bs2000_account(cmd_parms *cmd, void *dummy, char *name)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    return os_set_account(cmd->pool, name);
}