            /* The following extensions are not 'Found'.  That is, they don't
             * make any contribution to metadata negotation, so they must have
             * been explicitly requested by name. 
             */
            if (exinfo->handler && r->proxyreq == PROXYREQ_NONE) {
                r->handler = exinfo->handler;
                if (conf->multimatch & MULTIMATCH_HANDLERS)
                    found = 1;
            }
            /* XXX Two significant problems; 1, we don't check to see if we are
             * setting redundant filters.    2, we insert these in the types config
             * hook, which may be too early (dunno.)
             */
            if (exinfo->input_filters && r->proxyreq == PROXYREQ_NONE) {
                const char *filter, *filters = exinfo->input_filters;
                while (*filters 
                    && (filter = ap_getword(r->pool, &filters, ';'))) {
                    ap_add_input_filter(filter, NULL, r, r->connection);
                }
                if (conf->multimatch & MULTIMATCH_FILTERS)
                    found = 1;
            }
            if (exinfo->output_filters && r->proxyreq == PROXYREQ_NONE) {
                const char *filter, *filters = exinfo->output_filters;
                while (*filters 
                    && (filter = ap_getword(r->pool, &filters, ';'))) {
                    ap_add_output_filter(filter, NULL, r, r->connection);
                }
                if (conf->multimatch & MULTIMATCH_FILTERS)
                    found = 1;
            }
        }

        if (found || (conf->multimatch & MULTIMATCH_ANY))
            found_metadata = 1;
        else
            *((const char **) apr_array_push(exception_list)) = ext;
    }

    /*
     * Need to set a notes entry on r for unrecognized elements.
     * Somebody better claim them!  If we did absolutely nothing,
     * skip the notes to alert mod_negotiation we are clueless.
