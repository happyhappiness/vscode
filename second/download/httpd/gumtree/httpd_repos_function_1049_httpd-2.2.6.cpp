static const char *add_redirect_regex(cmd_parms *cmd, void *dirconf,
                                      const char *arg1, const char *arg2,
                                      const char *arg3)
{
    return add_redirect_internal(cmd, dirconf, arg1, arg2, arg3, 1);
}