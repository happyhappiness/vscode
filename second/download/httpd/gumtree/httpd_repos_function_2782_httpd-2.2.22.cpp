static void dbd_freetds_init(apr_pool_t *pool)
{
    int rv = regcomp(&dbd_freetds_find_arg,
                     "%(\\{[^}]*\\})?([0-9]*)[A-Za-z]", REG_EXTENDED);
    if (rv != 0) {
        char errmsg[256];
        regerror(rv, &dbd_freetds_find_arg, errmsg, 256);
        fprintf(stderr, "regcomp failed: %s\n", errmsg);
    }
    dbinit();
    dberrhandle(freetds_err_handler);
    apr_pool_cleanup_register(pool, NULL, freetds_term, apr_pool_cleanup_null);
}