static apr_status_t free_result(void *data)
{
    mysql_free_result(data);
    return APR_SUCCESS;
}