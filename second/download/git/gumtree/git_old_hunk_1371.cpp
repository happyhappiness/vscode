	tag = argv[0];

	object_ref = argc == 2 ? argv[1] : "HEAD";
	if (argc > 2)
		die(_("too many params"));

	if (get_sha1(object_ref, object))
		die(_("Failed to resolve '%s' as a valid ref."), object_ref);

	if (strbuf_check_tag_ref(&ref, tag))
		die(_("'%s' is not a valid tag name."), tag);

	if (read_ref(ref.buf, prev))
		hashclr(prev);
	else if (!force)
		die(_("tag '%s' already exists"), tag);

	opt.message_given = msg.given || msgfile;

	if (!cleanup_arg || !strcmp(cleanup_arg, "strip"))
