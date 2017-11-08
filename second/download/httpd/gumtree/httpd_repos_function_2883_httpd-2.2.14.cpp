static apr_status_t free_mem(void *data)
{
    sqlite_freemem(data);
    return APR_SUCCESS;
}