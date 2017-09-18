                }
                ap_rputs(" /></th>", r);
            }
            else {
                ap_rputs("&nbsp;</th>", r);
            }

            ++cols;
        }
        ap_rputs("<th>", r);
        emit_link(r, "Name", K_NAME, keyid, direction,
                  colargs, static_columns);
        if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
            ap_rputs("</th><th>", r);
            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_SIZE)) {
            ap_rputs("</th><th>", r);
            emit_link(r, "Size", K_SIZE, keyid, direction,
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_DESC)) {
            ap_rputs("</th><th>", r);
            emit_link(r, "Description", K_DESC, keyid, direction,
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            breakrow = apr_psprintf(r->pool,
                                    "<tr><th colspan=\"%d\">"
