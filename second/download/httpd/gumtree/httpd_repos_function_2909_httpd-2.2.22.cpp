static apr_status_t free_table(void *data)
{
    sqlite_free_table(data); 
    return APR_SUCCESS;
}