static apr_status_t freetds_regfree(void *rx)
{
    regfree((regex_t*)rx);
    return APR_SUCCESS;
}