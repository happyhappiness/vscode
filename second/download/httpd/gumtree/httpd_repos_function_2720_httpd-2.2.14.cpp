static apr_status_t clear_result(void *data)
{
    /* clear cursor */
    return (dbcanquery((DBPROCESS*)data) == SUCCEED)
            ? APR_SUCCESS
            : APR_EGENERAL;
}