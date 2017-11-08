static int push_refs_with_push(struct transport *transport,
			       struct ref *remote_refs, int flags)
{
	int force_all = flags & TRANSPORT_PUSH_FORCE;
	int mirror = flags & TRANSPORT_PUSH_MIRROR;
	struct helper_data *data = transport->data;
	struct strbuf buf = STRBUF_INIT;
	struct ref *ref;
	struct string_list cas_options = STRING_LIST_INIT_DUP;
	struct string_list_item *cas_option;

	get_helper(transport);
	if (!data->push)
		return 1;

	for (ref = remote_refs; ref; ref = ref->next) {
		if (!ref->peer_ref && !mirror)
			continue;

		/* Check for statuses set by set_ref_status_for_push() */
		switch (ref->status) {
		case REF_STATUS_REJECT_NONFASTFORWARD:
		case REF_STATUS_REJECT_STALE:
		case REF_STATUS_REJECT_ALREADY_EXISTS:
		case REF_STATUS_UPTODATE:
			continue;
		default:
			; /* do nothing */
		}

		if (force_all)
			ref->force = 1;

		strbuf_addstr(&buf, "push ");
		if (!ref->deletion) {
			if (ref->force)
				strbuf_addch(&buf, '+');
			if (ref->peer_ref)
				strbuf_addstr(&buf, ref->peer_ref->name);
			else
				strbuf_addstr(&buf, sha1_to_hex(ref->new_sha1));
		}
		strbuf_addch(&buf, ':');
		strbuf_addstr(&buf, ref->name);
		strbuf_addch(&buf, '\n');

		/*
		 * The "--force-with-lease" options without explicit
		 * values to expect have already been expanded into
		 * the ref->old_sha1_expect[] field; we can ignore
		 * transport->smart_options->cas altogether and instead
		 * can enumerate them from the refs.
		 */
		if (ref->expect_old_sha1) {
			struct strbuf cas = STRBUF_INIT;
			strbuf_addf(&cas, "%s:%s",
				    ref->name, sha1_to_hex(ref->old_sha1_expect));
			string_list_append(&cas_options, strbuf_detach(&cas, NULL));
		}
	}
	if (buf.len == 0) {
		string_list_clear(&cas_options, 0);
		return 0;
	}

	standard_options(transport);
	for_each_string_list_item(cas_option, &cas_options)
		set_helper_option(transport, "cas", cas_option->string);

	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", data->name);
	} else if (flags & TRANSPORT_PUSH_CERT) {
		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
			die("helper %s does not support --signed", data->name);
	}

	strbuf_addch(&buf, '\n');
	sendline(data, &buf);
	strbuf_release(&buf);

	return push_update_refs_status(data, remote_refs, flags);
}