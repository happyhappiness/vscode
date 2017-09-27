             */
            ap_remove_input_filter_byhandle(r->input_filters, "http_in");
            ap_remove_input_filter_byhandle(r->input_filters, "reqtimeout");
            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
            
            /* Ok, start an h2_conn on this one. */
            h2_ctx_server_set(ctx, r->server);
            status = h2_conn_setup(ctx, r->connection, r);
            if (status != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03088)
                              "session setup");
                return status;
            }
            
            h2_conn_run(ctx, c);
            return DONE;
        }
        return DONE;
    }
    
    return DECLINED;
}
