static apr_status_t bucket_cleanup(void *data)
{
    h2_stream **pstream = data;

    if (*pstream) {
        /*
         * If bucket_destroy is called after us, this prevents
         * bucket_destroy from trying to destroy the pool again.
         */
        *pstream = NULL;
    }
    return APR_SUCCESS;
}