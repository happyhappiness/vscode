static apr_status_t thread_end(void *data)
{
    mysql_thread_end();
    return APR_SUCCESS;
}