static int push_refs_with_export(struct transport *transport,
		struct ref *remote_refs, int flags)
{
	struct ref *ref;
	struct child_process *helper, exporter;
	struct helper_data *data = transport->data;
	struct string_list revlist_args = STRING_LIST_INIT_NODUP;
	struct strbuf buf = STRBUF_INIT;

	if (!data->refspecs)
		die("remote-helper doesn't support push; refspec needed");

	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", data->name);
	}

	if (flags & TRANSPORT_PUSH_FORCE) {
		if (set_helper_option(transport, "force", "true") != 0)
			warning("helper %s does not support 'force'", data->name);
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
		strbuf_addf(&buf, "%s.tmp", data->export_marks);
		rename(buf.buf, data->export_marks);
		strbuf_release(&buf);
	}

	return 0;
}