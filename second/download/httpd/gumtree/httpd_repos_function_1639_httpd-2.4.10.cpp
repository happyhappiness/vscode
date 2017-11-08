static apr_array_header_t *get_arguments(apr_pool_t * pool, const char *line)
{
    apr_array_header_t *args = apr_array_make(pool, 1, sizeof(char *));

    trim(line);
    while (*line) {
        char *arg = ap_getword_conf(pool, &line);
        char **new = apr_array_push(args);
        *new = arg;
        trim(line);
    }

    return args;
}