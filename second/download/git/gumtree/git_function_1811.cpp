static int push_refs_with_export(struct transport *transport,
		struct ref *remote_refs, int flags)
{
	struct ref *ref;
	struct child_process *helper, exporter;
	struct helper_data *data = transport->data;
	struct string_list revlist_args = STRING_LIST_INIT_DUP;
	struct strbuf buf = STRBUF_INIT;

	if (!data->refspecs)
		die("remote-helper doesn't support push; refspec needed");

	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", data->name);
	} else if (flags & TRANSPORT_PUSH_CERT) {
		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
			die("helper %s does not support dry-run", data->name);
	}

	if (flags & TRANSPORT_PUSH_FORCE) {
		if (set_helper_option(transport, "force", "true") != 0)
			warning("helper %s does not support 'force'", data->name);
	}

	helper = get_helper(transport);

	write_constant(helper->in, "export\n");

	for (ref = remote_refs; ref; ref = ref->next) {
		char *private;
		unsigned char sha1[20];

		private = apply_refspecs(data->refspecs, data->refspec_nr, ref->name);
		if (private && !get_sha1(private, sha1)) {
			strbuf_addf(&buf, "^%s", private);
			string_list_append(&revlist_args, strbuf_detach(&buf, NULL));
			hashcpy(ref->old_sha1, sha1);
		}
		free(private);

		if (ref->peer_ref) {
			if (strcmp(ref->name, ref->peer_ref->name)) {
				if (!ref->deletion) {
					const char *name;
					int flag;

					/* Follow symbolic refs (mainly for HEAD). */
					name = resolve_ref_unsafe(
						 ref->peer_ref->name,
						 RESOLVE_REF_READING,
						 sha1, &flag);
					if (!name || !(flag & REF_ISSYMREF))
						name = ref->peer_ref->name;

					strbuf_addf(&buf, "%s:%s", name, ref->name);
				} else
					strbuf_addf(&buf, ":%s", ref->name);

				string_list_append(&revlist_args, "--refspec");
				string_list_append(&revlist_args, buf.buf);
				strbuf_release(&buf);
			}
			if (!ref->deletion)
				string_list_append(&revlist_args, ref->peer_ref->name);
		}
	}

	if (get_exporter(transport, &exporter, &revlist_args))
		die("Couldn't run fast-export");

	string_list_clear(&revlist_args, 1);

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