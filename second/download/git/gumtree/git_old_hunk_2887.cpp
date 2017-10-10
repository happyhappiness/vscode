		if (starts_with(buffer, "author "))
			author = buffer + 7;
		buffer = eol;
	}
	if (!author) {
		warning(_("Missing author: %s"),
		    sha1_to_hex(commit->object.sha1));
		return;
	}
	if (log->user_format) {
		struct pretty_print_context ctx = {0};
		ctx.fmt = CMIT_FMT_USERFORMAT;
		ctx.abbrev = log->abbrev;
