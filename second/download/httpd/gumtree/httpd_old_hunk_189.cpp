			d->icon_height,
			d->icon_width
		    );
	    }
	    ap_rputs("> ", r);
	}
        emit_link(r, "Name", K_NAME, keyid, direction, static_columns);
	ap_rputs("                   ", r);
	if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,
                      static_columns);
	    ap_rputs("       ", r);
	}
	if (!(autoindex_opts & SUPPRESS_SIZE)) {
