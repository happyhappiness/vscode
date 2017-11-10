static apr_status_t free_mem(void *data)
{
    sqlite3_free(data);
    return APR_SUCCESS;
}