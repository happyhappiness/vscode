static int create_table(apr_pool_t* pool, apr_dbd_t* handle,
                        const apr_dbd_driver_t* driver)
{
    int rv = 0;
    int nrows;
    const char *statement = "CREATE TABLE apr_dbd_test ("
        "col1 varchar(40) not null,"
        "col2 varchar(40),"
        "col3 integer)" ;
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    return rv;
}