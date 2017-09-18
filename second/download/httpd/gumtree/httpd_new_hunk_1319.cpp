                         p_conn->name ? p_conn->name: "",
                         c->remote_ip, c->remote_host ? c->remote_host: "");
            return status;
        }

        apr_brigade_length(temp_brigade, 1, &bytes);
        bytes_read += bytes;

        /*
         * Save temp_brigade in input_brigade. (At least) in the SSL case
         * temp_brigade contains transient buckets whose data would get
         * overwritten during the next call of ap_get_brigade in the loop.
         * ap_save_brigade ensures these buckets to be set aside.
         * Calling ap_save_brigade with NULL as filter is OK, because
         * input_brigade already has been created and does not need to get
         * created by ap_save_brigade.
         */
        status = ap_save_brigade(NULL, &input_brigade, &temp_brigade, p);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                         "proxy: processing prefetched request body failed"
                         " to %s from %s (%s)",
                         p_conn->name ? p_conn->name: "",
                         c->remote_ip, c->remote_host ? c->remote_host: "");
            return status;
        }

    /* Ensure we don't hit a wall where we have a buffer too small
     * for ap_get_brigade's filters to fetch us another bucket,
     * surrender once we hit 80 bytes less than MAX_MEM_SPOOL
     * (an arbitrary value.)
     */
    } while ((bytes_read < MAX_MEM_SPOOL - 80) 
