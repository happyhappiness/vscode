static const char *filter_bytype(cmd_parms *cmd, void *CFG,
                                 int argc, char *const argv[])
{
    /* back compatibility, need to parse multiple components in filter name */
    char *pname;
    char *strtok_state = NULL;
    char *name;
    const char **types;
    const char *rv = NULL;
    if (argc < 2)
        return "AddOutputFilterByType requires at least two arguments";
    name = apr_pstrdup(cmd->temp_pool, argv[0]);
    types = apr_palloc(cmd->pool, argc * sizeof(char *));
    memcpy(types, &argv[1], (argc - 1) * sizeof(char *));
    types[argc-1] = NULL;
    for (pname = apr_strtok(name, ";", &strtok_state);
         pname != NULL && rv == NULL;
         pname = apr_strtok(NULL, ";", &strtok_state)) {
        rv = filter_bytype1(cmd, CFG, pname, types);
    }
    return rv;
}