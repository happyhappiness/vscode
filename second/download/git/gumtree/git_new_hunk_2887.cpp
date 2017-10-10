		if (starts_with(buffer, "author "))
			author = buffer + 7;
		buffer = eol;
	}
	if (!author) {
		warning(_("Missing author: %s"),
		    oid_to_hex(&commit->object.oid));
		return;
	}
	if (log->user_format) {
		struct pretty_print_context ctx = {0};
		ctx.fmt = CMIT_FMT_USERFORMAT;
		ctx.abbrev = log->abbrev;
