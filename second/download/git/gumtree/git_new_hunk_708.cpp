		die(_("--contains option is only allowed with -l."));
	if (filter.points_at.nr)
		die(_("--points-at option is only allowed with -l."));
	if (filter.merge_commit)
		die(_("--merged and --no-merged option are only allowed with -l"));
	if (cmdmode == 'd')
		return for_each_tag_name(argv, delete_tag, NULL);
	if (cmdmode == 'v') {
		if (format)
			verify_ref_format(format);
		return for_each_tag_name(argv, verify_tag, format);
	}

	if (msg.given || msgfile) {
		if (msg.given && msgfile)
			die(_("only one -F or -m option is allowed."));
		if (msg.given)
			strbuf_addbuf(&buf, &(msg.buf));
