static int test_pquery(apr_pool_t* pool, apr_dbd_t* handle,
                       const apr_dbd_driver_t* driver)
{
    int rv = 0;
    const char *query = "INSERT INTO apr_dbd_test VALUES (%s, %s, %d)";
    apr_dbd_prepared_t *statement = NULL;
    const char *label = "testpquery";
    int nrows;
    apr_dbd_transaction_t *trans =0;

    rv = apr_dbd_prepare(driver, pool, handle, query, label, &statement);
    /* rv = apr_dbd_prepare(driver, pool, handle, query, NULL, &statement); */
    if (rv) {
        printf("Prepare statement failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    apr_dbd_transaction_start(driver, pool, handle, &trans);
    rv = apr_dbd_pvquery(driver, pool, handle, &nrows, statement,
                         "prepared", "insert", "2", NULL);
    apr_dbd_transaction_end(driver, pool, trans);
    if (rv) {
        printf("Exec of prepared statement failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    printf("Showing table (should now contain row \"prepared insert 2\")\n");
    select_sequential(pool, handle, driver);
    return rv;
}