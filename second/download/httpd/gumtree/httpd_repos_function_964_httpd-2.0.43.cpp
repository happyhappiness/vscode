static const char *cmd_rewriteoptions_setoption(apr_pool_t *p, int *options,
                                                const char *name)
{
    if (strcasecmp(name, "inherit") == 0) {
        *options |= OPTION_INHERIT;
    }
    else {
        return apr_pstrcat(p, "RewriteOptions: unknown option '",
                          name, "'", NULL);
    }
    return NULL;
}