        if (APR_STATUS_IS_TIMEUP(rv)) {
            /*
             * Notice a timeout as an error message. This might be
             * valuable for detecting clients with broken network
             * connections or possible DoS attacks.
             *
             * It is still safe to use r / r->pool here as the eor bucket
             * could not have been destroyed in the event of a timeout.
             */
            ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, r, APLOGNO(01581)
                          "Timeout while writing data for URI %s to the"
                          " client", r->unparsed_uri);
        }
    }
    if (ap_extended_status) {
        ap_time_process_request(c->sbh, STOP_PREQUEST);
