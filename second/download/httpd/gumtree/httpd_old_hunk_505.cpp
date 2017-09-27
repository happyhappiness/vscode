                         p_conn->name ? p_conn->name: "",
                         c->remote_ip, c->remote_host ? c->remote_host: "");
            return status;
        }

        apr_brigade_length(temp_brigade, 1, &bytes);
        APR_BRIGADE_CONCAT(input_brigade, temp_brigade);
        bytes_read += bytes;

    /* Ensure we don't hit a wall where we have a buffer too small
     * for ap_get_brigade's filters to fetch us another bucket,
     * surrender once we hit 80 bytes less than MAX_MEM_SPOOL
     * (an arbitrary value.)
     */
    } while ((bytes_read < MAX_MEM_SPOOL - 80) 
