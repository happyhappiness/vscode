static apr_status_t freetds_term(void *dummy)
{
    dbexit();
    regfree(&dbd_freetds_find_arg);
    return APR_SUCCESS;
}