		if (config_cover_letter == COVER_AUTO)
			cover_letter = (total > 1);
		else
			cover_letter = (config_cover_letter == COVER_ON);
	}

	if (!signature) {
		; /* --no-signature inhibits all signatures */
	} else if (signature && signature != git_version_string) {
		; /* non-default signature already set */
	} else if (signature_file) {
		struct strbuf buf = STRBUF_INIT;

		if (strbuf_read_file(&buf, signature_file, 128) < 0)
			die_errno(_("unable to read signature file '%s'"), signature_file);
		signature = strbuf_detach(&buf, NULL);
	}

	if (in_reply_to || thread || cover_letter)
		rev.ref_message_ids = xcalloc(1, sizeof(struct string_list));
	if (in_reply_to) {
		const char *msgid = clean_message_id(in_reply_to);
		string_list_append(rev.ref_message_ids, msgid);
	}
