static apr_status_t stmt_close(void *data)
{
    mysql_stmt_close(data);
    return APR_SUCCESS;
}