static apr_status_t regex_cleanup(void *preg)
{
    regfree((regex_t *) preg);
    return APR_SUCCESS;
}