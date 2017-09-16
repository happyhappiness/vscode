			d->icon_height,

			d->icon_width

		    );

	    }

	    ap_rputs("> ", r);

	}

        emit_link(r, widthify("Name", name_scratch,

			      (name_width > 5) ? 5 : name_width, K_NOPAD),

		  K_NAME, keyid, direction, static_columns);

	if (name_width > 5) {

	    memset(name_scratch, ' ', name_width);

	    name_scratch[name_width] = '\0';

	    ap_rputs(&name_scratch[5], r);

	}

	/*

	 * Emit the guaranteed-at-least-one-space-between-columns byte.

	 */

	ap_rputs(" ", r);

	if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {

            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,

                      static_columns);

	    ap_rputs("       ", r);

	}

	if (!(autoindex_opts & SUPPRESS_SIZE)) {

