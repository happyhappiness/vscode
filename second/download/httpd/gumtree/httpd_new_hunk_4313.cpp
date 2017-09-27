        }
    }

    if (cs->pub.state == CONN_STATE_WRITE_COMPLETION) {
        ap_filter_t *output_filter = c->output_filters;
        apr_status_t rv;
        ap_update_child_status(sbh, SERVER_BUSY_WRITE, NULL);
        while (output_filter->next != NULL) {
            output_filter = output_filter->next;
        }
        rv = output_filter->frec->filter_func.out_func(output_filter, NULL);
        if (rv != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c, APLOGNO(00470)
