static apr_size_t dbd_oracle_long_size_set(apr_dbd_t *sql,
                                           apr_size_t long_size)
{
    apr_size_t old_size = sql->long_size;
    sql->long_size = long_size;
    return old_size;
}