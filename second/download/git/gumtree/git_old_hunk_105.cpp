		if (config_cover_letter == COVER_AUTO)
			cover_letter = (total > 1);
		else
			cover_letter = (config_cover_letter == COVER_ON);
	}

	if (in_reply_to || thread || cover_letter)
		rev.ref_message_ids = xcalloc(1, sizeof(struct string_list));
	if (in_reply_to) {
		const char *msgid = clean_message_id(in_reply_to);
		string_list_append(rev.ref_message_ids, msgid);
	}
