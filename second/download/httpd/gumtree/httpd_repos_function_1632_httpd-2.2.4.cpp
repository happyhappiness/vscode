static const char *add_charset_default(cmd_parms *cmd, void *in_dc,
                                       const char *name)
{
    charset_dir_t *dc = in_dc;

    dc->charset_default = name;
    return NULL;
}