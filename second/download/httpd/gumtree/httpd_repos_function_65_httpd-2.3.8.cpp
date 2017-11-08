static void usage_repeated_arg(apr_pool_t *pool, char option) {
    usage(apr_psprintf(pool, 
                       "The option '%c' cannot be specified more than once",
                       option));
}