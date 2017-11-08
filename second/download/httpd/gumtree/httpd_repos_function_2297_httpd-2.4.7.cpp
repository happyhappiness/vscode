static const char *filter_provider(cmd_parms *cmd, void *CFG,
                                   const char *fname, const char *pname,
                                   const char *expr)
{
    return add_filter(cmd, CFG, fname, pname, expr, NULL);
}