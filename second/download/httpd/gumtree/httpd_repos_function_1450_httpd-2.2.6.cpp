static const char *
    add_pass_regex(cmd_parms *cmd, void *dummy, const char *arg)
{
    return add_pass(cmd, dummy, arg, 1);
}