static int parse_directives(char *name, char *val)
{
    if (strcasecmp(name, "&include") == 0)
        return include_config(val, 1);
    if (strcasecmp(name, "&merge") == 0)
        return include_config(val, 0);
    rprintf(FLOG, "Unknown directive: %s.\n", name);
    return 0;
}