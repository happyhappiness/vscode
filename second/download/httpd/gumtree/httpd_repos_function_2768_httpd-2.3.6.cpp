static apr_status_t eor_bucket_cleanup(void *data)
{
    apr_bucket *b = (apr_bucket *)data;
    request_rec *r = (request_rec *)b->data;

    if (r != NULL) {
        /*
         * If eor_bucket_destroy is called after us, this prevents
         * eor_bucket_destroy from trying to destroy the pool again.
         */
        b->data = NULL;
        /* Update child status and log the transaction */
        ap_update_child_status(r->connection->sbh, SERVER_BUSY_LOG, r);
        ap_run_log_transaction(r);
        if (ap_extended_status) {
            ap_increment_counts(r->connection->sbh, r);
        }
    }
    return APR_SUCCESS;
}