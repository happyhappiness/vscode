		name = posn->symref ? posn->symref : posn->name;
		if (data->refspecs)
			private = apply_refspecs(data->refspecs, data->refspec_nr, name);
		else
			private = xstrdup(name);
		if (private) {
			if (read_ref(private, posn->old_sha1) < 0)
				die("Could not read ref %s", private);
			free(private);
		}
	}
	strbuf_release(&buf);
	return 0;
