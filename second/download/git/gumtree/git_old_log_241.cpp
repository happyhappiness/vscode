die(_("patch fragment without header at line %d: %.*s"),
			    state->linenr, (int)len-1, line);