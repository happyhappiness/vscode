                if (d->icon_width) {
                    ap_rprintf(r, " width=\"%d\"", d->icon_width);
                }
                if (d->icon_height) {
                    ap_rprintf(r, " height=\"%d\"", d->icon_height);
                }
                ap_rputs(" /> ", r);
            }
            else {
                ap_rputs("      ", r);
            }
        }
        emit_link(r, "Name", K_NAME, keyid, direction, 
                  colargs, static_columns);
        ap_rputs(pad_scratch + 4, r);
        /*
         * Emit the guaranteed-at-least-one-space-between-columns byte.
         */
        ap_rputs(" ", r);
        if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,
                      colargs, static_columns);
            ap_rputs("      ", r);
        }
        if (!(autoindex_opts & SUPPRESS_SIZE)) {
            emit_link(r, "Size", K_SIZE, keyid, direction, 
                      colargs, static_columns);
            ap_rputs("  ", r);
        }
        if (!(autoindex_opts & SUPPRESS_DESC)) {
            emit_link(r, "Description", K_DESC, keyid, direction,
                      colargs, static_columns);
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            ap_rputs("<hr />", r);
        }
        else {
            ap_rputc('\n', r);
        }
    }
    else {
