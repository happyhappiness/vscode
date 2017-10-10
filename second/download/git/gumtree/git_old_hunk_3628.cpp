
			strbuf_reset(&note);
			if (ref) {
				rc |= update_local_ref(ref, what, rm, &note);
				free(ref);
			} else
				strbuf_addf(&note, "* %-*s %-*s -> FETCH_HEAD",
					    TRANSPORT_SUMMARY_WIDTH,
					    *kind ? kind : "branch",
					    REFCOL_WIDTH,
					    *what ? what : "HEAD");
			if (note.len) {
				if (verbosity >= 0 && !shown_url) {
					fprintf(stderr, _("From %.*s\n"),
							url_len, url);
					shown_url = 1;
				}
