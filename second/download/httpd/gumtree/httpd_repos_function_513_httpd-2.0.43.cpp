static const char *request_header_cmd(cmd_parms *cmd, void *indirconf,
                              const char *action, const char *inhdr,
                              const char *value)
{
    return header_inout_cmd(hdr_in, cmd, indirconf, action, inhdr, value, NULL);
}