			ls->dentry_name, repo->url);
		aborted = 1;
		free(ref);
		return;
	}

	o = parse_object(&ref->old_oid);
	if (!o) {
		fprintf(stderr,
			"Unable to parse object %s for remote ref %s\n",
			oid_to_hex(&ref->old_oid), ls->dentry_name);
		aborted = 1;
		free(ref);
