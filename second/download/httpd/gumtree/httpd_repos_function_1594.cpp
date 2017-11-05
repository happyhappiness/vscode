static void check_pipeline(conn_rec *c)
{
    if (c->keepalive != AP_CONN_CLOSE) {
        apr_status_t rv;
        apr_bucket_brigade *bb = apr_brigade_create(c->pool, c->bucket_alloc);

        rv = ap_get_brigade(c->input_filters, bb, AP_MODE_SPECULATIVE,
                            APR_NONBLOCK_READ, 1);
        if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(bb)) {
            /*
             * Error or empty brigade: There is no data present in the input
             * filter
             */
            c->data_in_input_filters = 0;
        }
        else {
            c->data_in_input_filters = 1;
        }
        apr_brigade_destroy(bb);
    }
}