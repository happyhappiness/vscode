static apr_status_t clear_result(void *data)
{
    PQclear(data);
    return APR_SUCCESS;
}