static const char *add_alias(cmd_parms *cmd, void *dummy, const char *fake,
                             const char *real)
{
    return add_alias_internal(cmd, dummy, fake, real, 0);
}