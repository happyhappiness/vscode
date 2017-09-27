{
    ap_die_r(type, r, r->status);
}

static void check_pipeline(conn_rec *c, apr_bucket_brigade *bb)
{
    if (c->keepalive != AP_CONN_CLOSE && !c->aborted) {
        apr_status_t rv;

        AP_DEBUG_ASSERT(APR_BRIGADE_EMPTY(bb));
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
    }
}


AP_DECLARE(void) ap_process_request_after_handler(request_rec *r)
