static apr_status_t bucket_cleanup(void *data)
{
    h2_session **psession = data;

    if (*psession) {
        /*
         * If bucket_destroy is called after us, this prevents
         * bucket_destroy from trying to destroy the pool again.
         */
        *psession = NULL;
    }
    return APR_SUCCESS;
}