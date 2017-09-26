    new->read_length     = r->read_length;     /* We can only read it once */
    new->vlist_validator = r->vlist_validator;

    new->proto_output_filters  = r->proto_output_filters;
    new->proto_input_filters   = r->proto_input_filters;

    new->output_filters  = new->proto_output_filters;
    new->input_filters   = new->proto_input_filters;

    if (new->main) {
        /* Add back the subrequest filter, which we lost when
         * we set output_filters to include only the protocol
         * output filters from the original request.
         */
        ap_add_output_filter_handle(ap_subreq_core_filter_handle,
                                    NULL, new, new->connection);
    }

    update_r_in_filters(new->input_filters, r, new);
    update_r_in_filters(new->output_filters, r, new);

    apr_table_setn(new->subprocess_env, "REDIRECT_STATUS",
