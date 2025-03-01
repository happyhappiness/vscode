             */
            ap_remove_input_filter_byhandle(r->input_filters, "http_in");
            ap_remove_input_filter_byhandle(r->input_filters, "reqtimeout");
            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
            
            /* Ok, start an h2_conn on this one. */
            status = h2_conn_process(r->connection, r, r->server);
            if (status != DONE) {
                /* Nothing really to do about this. */
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                              "session proessed, unexpected status");
            }
        }
        return DONE;
    }
    
    return DECLINED;
}
