static const char *set_default_type(cmd_parms *cmd, void *d_,
                                   const char *arg)
{
    if ((strcasecmp(arg, "off") != 0) && (strcasecmp(arg, "none") != 0)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
              "Ignoring deprecated use of DefaultType in line %d of %s.",
                     cmd->directive->line_num, cmd->directive->filename);
    }

    return NULL;
}