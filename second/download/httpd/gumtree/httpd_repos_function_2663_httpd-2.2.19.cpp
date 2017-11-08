static int invalid_op(apr_pool_t* pool, apr_dbd_t* handle,
                      const apr_dbd_driver_t* driver)
{
    int rv = 0;
    int nrows;
    const char *statement = "INSERT into apr_dbd_test1 (col2) values ('foo')" ;
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    printf("invalid op returned %d (should be nonzero).  Error msg follows\n", rv);
    printf("'%s'\n", apr_dbd_error(driver, handle, rv));
    statement = "INSERT into apr_dbd_test (col1, col2) values ('bar', 'foo')" ;
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    printf("valid op returned %d (should be zero; error shouldn't affect subsequent ops)\n", rv);
    return rv;
}