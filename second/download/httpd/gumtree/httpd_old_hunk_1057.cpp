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
