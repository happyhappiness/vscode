             */
            discard_script_output(bb);
            apr_brigade_destroy(bb);
            return HTTP_MOVED_TEMPORARILY;
        }

        ap_pass_brigade(r->output_filters, bb);
    }

    if (nph) {
        conn_rec *c = r->connection;
        struct ap_filter_t *cur;

