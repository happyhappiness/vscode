
			strbuf_reset(&note);
			if (ref) {
				rc |= update_local_ref(ref, what, rm, &note);
				free(ref);
			} else
				format_display(&note, '*',
					       *kind ? kind : "branch", NULL,
					       *what ? what : "HEAD",
					       "FETCH_HEAD");
			if (note.len) {
				if (verbosity >= 0 && !shown_url) {
					fprintf(stderr, _("From %.*s\n"),
							url_len, url);
					shown_url = 1;
				}
