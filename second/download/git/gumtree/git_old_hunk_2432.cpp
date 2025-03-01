		name = posn->symref ? posn->symref : posn->name;
		if (data->refspecs)
			private = apply_refspecs(data->refspecs, data->refspec_nr, name);
		else
			private = xstrdup(name);
		if (private) {
			read_ref(private, posn->old_sha1);
			free(private);
		}
	}
	strbuf_release(&buf);
	return 0;
}
