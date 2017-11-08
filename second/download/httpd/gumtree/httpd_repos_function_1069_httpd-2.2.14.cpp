static const char *add_alias(cmd_parms *cmd, void *dummy, const char *f,
                             const char *r)
{
    return add_alias_internal(cmd, dummy, f, r, 0);
}