
		if (strbuf_read_file(&buf, signature_file, 128) < 0)
			die_errno(_("unable to read signature file '%s'"), signature_file);
		signature = strbuf_detach(&buf, NULL);
	}

	memset(&bases, 0, sizeof(bases));
	if (base_commit || base_auto) {
		struct commit *base = get_base_commit(base_commit, list, nr);
		reset_revision_walk();
		prepare_bases(&bases, base, list, nr);
	}

	if (in_reply_to || thread || cover_letter)
		rev.ref_message_ids = xcalloc(1, sizeof(struct string_list));
	if (in_reply_to) {
		const char *msgid = clean_message_id(in_reply_to);
		string_list_append(rev.ref_message_ids, msgid);
	}
