        }
        if (!(autoindex_opts & SUPPRESS_DESC)) {
            emit_link(r, "Description", K_DESC, keyid, direction,
                      colargs, static_columns);
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            ap_rputs("<hr", r);
            if (autoindex_opts & EMIT_XHTML) {
                ap_rputs(" /", r);
            }
            ap_rputs(">", r);
        }
        else {
            ap_rputc('\n', r);
        }
    }
    else {
