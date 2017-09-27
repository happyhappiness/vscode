                                                      exinfo->encoding_type,
                                                      NULL);
                }
                found = 1;
            }
            /* The following extensions are not 'Found'.  That is, they don't
             * make any contribution to metadata negotiation, so they must have
             * been explicitly requested by name.
             */
            if (exinfo->handler && r->proxyreq == PROXYREQ_NONE) {
                r->handler = exinfo->handler;
                if (conf->multimatch & MULTIMATCH_HANDLERS) {
                    found = 1;
                }
            }
            /* XXX Two significant problems; 1, we don't check to see if we are
             * setting redundant filters.    2, we insert these in the types
             * config hook, which may be too early (dunno.)
             */
            if (exinfo->input_filters) {
                const char *filter, *filters = exinfo->input_filters;
                while (*filters
                    && (filter = ap_getword(r->pool, &filters, ';'))) {
                    ap_add_input_filter(filter, NULL, r, r->connection);
                }
                if (conf->multimatch & MULTIMATCH_FILTERS) {
                    found = 1;
                }
            }
            if (exinfo->output_filters) {
                const char *filter, *filters = exinfo->output_filters;
                while (*filters
                    && (filter = ap_getword(r->pool, &filters, ';'))) {
                    ap_add_output_filter(filter, NULL, r, r->connection);
                }
                if (conf->multimatch & MULTIMATCH_FILTERS) {
