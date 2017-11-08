static apr_status_t privileges_term(void *rec)
{
    priv_freeset(priv_setid);
    return APR_SUCCESS;
}