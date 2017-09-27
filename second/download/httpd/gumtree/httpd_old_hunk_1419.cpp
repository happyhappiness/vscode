
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_TIMEUP(rv)) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else {
                r->status = HTTP_BAD_REQUEST;
            }

            /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
             * finding the end-of-line.  This is only going to happen if it
             * exceeds the configured limit for a field size.
