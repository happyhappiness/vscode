static int drop_table(apr_pool_t* pool, apr_dbd_t* handle,
                      const apr_dbd_driver_t* driver)
{
    int rv = 0;
    int nrows;
    const char *statement = "DROP TABLE apr_dbd_test" ;
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    return rv;
}