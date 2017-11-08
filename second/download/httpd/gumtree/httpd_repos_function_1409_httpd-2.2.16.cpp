static void check_pipeline_flush(request_rec *r)
{
    apr_bucket *e;
    apr_bucket_brigade *bb;
    conn_rec *c = r->connection;
    /* ### if would be nice if we could PEEK without a brigade. that would
       ### allow us to defer creation of the brigade to when we actually
       ### need to send a FLUSH. */
    bb = apr_brigade_create(r->pool, c->bucket_alloc);

    /* Flush the filter contents if:
     *
     *   1) the connection will be closed
     *   2) there isn't a request ready to be read
     */
    /* ### shouldn't this read from the connection input filters? */
    /* ### is zero correct? that means "read one line" */
    if (r->connection->keepalive != AP_CONN_CLOSE) {
        if (ap_get_brigade(r->input_filters, bb, AP_MODE_EATCRLF,
                       APR_NONBLOCK_READ, 0) != APR_SUCCESS) {
            c->data_in_input_filters = 0;  /* we got APR_EOF or an error */
        }
        else {
            c->data_in_input_filters = 1;
            return;    /* don't flush */
        }
    }

        e = apr_bucket_flush_create(c->bucket_alloc);

        /* We just send directly to the connection based filters.  At
         * this point, we know that we have seen all of the data
         * (request finalization sent an EOS bucket, which empties all
         * of the request filters). We just want to flush the buckets
         * if something hasn't been sent to the network yet.
         */
        APR_BRIGADE_INSERT_HEAD(bb, e);
        ap_pass_brigade(r->connection->output_filters, bb);
}