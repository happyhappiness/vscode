	}

	helper = get_helper(transport);

	write_constant(helper->in, "export\n");

	strbuf_reset(&buf);

	for (ref = remote_refs; ref; ref = ref->next) {
		char *private;
		unsigned char sha1[20];

		if (ref->deletion)
			die("remote-helpers do not support ref deletion");

		private = apply_refspecs(data->refspecs, data->refspec_nr, ref->name);
		if (private && !get_sha1(private, sha1)) {
			strbuf_addf(&buf, "^%s", private);
			string_list_append(&revlist_args, strbuf_detach(&buf, NULL));
			hashcpy(ref->old_sha1, sha1);
		}
		free(private);

		if (ref->peer_ref) {
			if (strcmp(ref->peer_ref->name, ref->name))
				die("remote-helpers do not support old:new syntax");
			string_list_append(&revlist_args, ref->peer_ref->name);
		}
	}

	if (get_exporter(transport, &exporter, &revlist_args))
		die("Couldn't run fast-export");

	if (finish_command(&exporter))
		die("Error while running fast-export");
	if (push_update_refs_status(data, remote_refs, flags))
		return 1;

	if (data->export_marks) {
