int main(int argc, char** argv)
{
    const char *name;
    const char *params;
    apr_pool_t *pool = NULL;
    apr_dbd_t *sql = NULL;
    const apr_dbd_driver_t *driver = NULL;
    int rv;

    apr_initialize();
    apr_pool_create(&pool, NULL);

    if (argc >= 2 && argc <= 3) {
        name = argv[1];
        params = ( argc == 3 ) ? argv[2] : "";
        apr_dbd_init(pool);
        setbuf(stdout,NULL);
        rv = apr_dbd_get_driver(pool, name, &driver);
        switch (rv) {
        case APR_SUCCESS:
           printf("Loaded %s driver OK.\n", name);
           break;
        case APR_EDSOOPEN:
           printf("Failed to load driver file apr_dbd_%s.so\n", name);
           goto finish;
        case APR_ESYMNOTFOUND:
           printf("Failed to load driver apr_dbd_%s_driver.\n", name);
           goto finish;
        case APR_ENOTIMPL:
           printf("No driver available for %s.\n", name);
           goto finish;
        default:        /* it's a bug if none of the above happen */
           printf("Internal error loading %s.\n", name);
           goto finish;
        }
        rv = apr_dbd_open(driver, pool, params, &sql);
        switch (rv) {
        case APR_SUCCESS:
           printf("Opened %s[%s] OK\n", name, params);
           break;
        case APR_EGENERAL:
           printf("Failed to open %s[%s]\n", name, params);
           goto finish;
        default:        /* it's a bug if none of the above happen */
           printf("Internal error opening %s[%s]\n", name, params);
           goto finish;
        }
        TEST("create table", create_table);
        TEST("insert rows", insert_rows);
        TEST("invalid op", invalid_op);
        TEST("select random", select_random);
        TEST("select sequential", select_sequential);
        TEST("transactions", test_transactions);
        TEST("prepared select", test_pselect);
        TEST("prepared query", test_pquery);
        TEST("drop table", drop_table);
        apr_dbd_close(driver, sql);
    }
    else {
        fprintf(stderr, "Usage: %s driver-name [params]\n", argv[0]);
    }
finish:
    apr_pool_destroy(pool);
    apr_terminate();
    return 0;
}