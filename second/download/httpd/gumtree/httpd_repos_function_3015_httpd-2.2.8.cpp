static apr_status_t brigade_cleanup(void *data) 
{
    return apr_brigade_cleanup(data);
}