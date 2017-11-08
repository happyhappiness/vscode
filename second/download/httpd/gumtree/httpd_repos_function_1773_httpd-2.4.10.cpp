static int mod_info_has_cmd(const command_rec * cmds, ap_directive_t * dir)
{
    const command_rec *cmd;
    if (cmds == NULL)
        return 1;
    for (cmd = cmds; cmd->name; ++cmd) {
        if (strcasecmp(cmd->name, dir->directive) == 0)
            return 1;
    }
    return 0;
}