
        f = new->output_filters;
        do {
            nextf = f->next;

            if (f->r == r && f->frec != ap_subreq_core_filter_handle) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "dropping filter '%s' in internal redirect from %s to %s",
                              f->frec->name, r->unparsed_uri, new_uri);

                /* To remove the filter, first set f->r to the *new*
                 * request_rec, so that ->output_filters on 'new' is
                 * changed (if necessary) when removing the filter. */
