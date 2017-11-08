static const char *filter_bytype(cmd_parms *cmd, void *CFG,
                                 const char *names, const char *type)
{
    /* back compatibility, need to parse multiple components in pname */
    char *pname;
    char *strtok_state = NULL;
    char *name = apr_pstrdup(cmd->temp_pool, names);
    const char *rv = NULL;
    for (pname = apr_strtok(name, ";", &strtok_state);
         pname != NULL && rv == NULL;
         pname = apr_strtok(NULL, ";", &strtok_state)) {
        rv = filter_bytype1(cmd, CFG, pname, type);
    }
    return rv;
}