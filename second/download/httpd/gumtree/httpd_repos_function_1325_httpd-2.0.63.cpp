static const char *parse_cmd(apr_pool_t *p, const char **args, ef_filter_t *filter)
{
    if (**args == '"') {
        const char *start = *args + 1;
        char *parms;
        int escaping = 0;
        apr_status_t rv;

        ++*args; /* move past leading " */
        /* find true end of args string (accounting for escaped quotes) */
        while (**args && (**args != '"' || (**args == '"' && escaping))) {
            if (escaping) {
                escaping = 0;
            }
            else if (**args == '\\') {
                escaping = 1;
            }
            ++*args;
        }
        if (**args != '"') {
            return "Expected cmd= delimiter";
        }
        /* copy *just* the arg string for parsing, */
        parms = apr_pstrndup(p, start, *args - start);
        ++*args; /* move past trailing " */

        /* parse and tokenize the args. */
        rv = apr_tokenize_to_argv(parms, &(filter->args), p);
        if (rv != APR_SUCCESS) {
            return "cmd= parse error";
        }
    }
    else
    {
        /* simple path */
        /* Allocate space for two argv pointers and parse the args. */
        filter->args = (char **)apr_palloc(p, 2 * sizeof(char *));
        filter->args[0] = ap_getword_white(p, args);
        filter->args[1] = NULL; /* end of args */
    }
    if (!filter->args[0]) {
        return "Invalid cmd= parameter";
    }
    filter->command = filter->args[0];
    
    return NULL;
}