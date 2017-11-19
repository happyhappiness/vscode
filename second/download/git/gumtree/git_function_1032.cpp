int cmd_tag(int argc, const char **argv, const char *prefix)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf ref = STRBUF_INIT;
	struct strbuf reflog_msg = STRBUF_INIT;
	unsigned char object[20], prev[20];
	const char *object_ref, *tag;
	struct create_tag_options opt;
	char *cleanup_arg = NULL;
	int create_reflog = 0;
	int annotate = 0, force = 0;
	int cmdmode = 0, create_tag_object = 0;
	const char *msgfile = NULL, *keyid = NULL;
	struct msg_arg msg = { 0, STRBUF_INIT };
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;
	struct ref_filter filter;
	static struct ref_sorting *sorting = NULL, **sorting_tail = &sorting;
	const char *format = NULL;
	int icase = 0;
	struct option options[] = {
		OPT_CMDMODE('l', "list", &cmdmode, N_("list tag names"), 'l'),
		{ OPTION_INTEGER, 'n', NULL, &filter.lines, N_("n"),
				N_("print <n> lines of each tag message"),
				PARSE_OPT_OPTARG, NULL, 1 },
		OPT_CMDMODE('d', "delete", &cmdmode, N_("delete tags"), 'd'),
		OPT_CMDMODE('v', "verify", &cmdmode, N_("verify tags"), 'v'),

		OPT_GROUP(N_("Tag creation options")),
		OPT_BOOL('a', "annotate", &annotate,
					N_("annotated tag, needs a message")),
		OPT_CALLBACK('m', "message", &msg, N_("message"),
			     N_("tag message"), parse_msg_arg),
		OPT_FILENAME('F', "file", &msgfile, N_("read message from file")),
		OPT_BOOL('s', "sign", &opt.sign, N_("annotated and GPG-signed tag")),
		OPT_STRING(0, "cleanup", &cleanup_arg, N_("mode"),
			N_("how to strip spaces and #comments from message")),
		OPT_STRING('u', "local-user", &keyid, N_("key-id"),
					N_("use another key to sign the tag")),
		OPT__FORCE(&force, N_("replace the tag if exists")),
		OPT_BOOL(0, "create-reflog", &create_reflog, N_("create a reflog")),

		OPT_GROUP(N_("Tag listing options")),
		OPT_COLUMN(0, "column", &colopts, N_("show tag list in columns")),
		OPT_CONTAINS(&filter.with_commit, N_("print only tags that contain the commit")),
		OPT_NO_CONTAINS(&filter.no_commit, N_("print only tags that don't contain the commit")),
		OPT_WITH(&filter.with_commit, N_("print only tags that contain the commit")),
		OPT_WITHOUT(&filter.no_commit, N_("print only tags that don't contain the commit")),
		OPT_MERGED(&filter, N_("print only tags that are merged")),
		OPT_NO_MERGED(&filter, N_("print only tags that are not merged")),
		OPT_CALLBACK(0 , "sort", sorting_tail, N_("key"),
			     N_("field name to sort on"), &parse_opt_ref_sorting),
		{
			OPTION_CALLBACK, 0, "points-at", &filter.points_at, N_("object"),
			N_("print only tags of the object"), PARSE_OPT_LASTARG_DEFAULT,
			parse_opt_object_name, (intptr_t) "HEAD"
		},
		OPT_STRING(  0 , "format", &format, N_("format"), N_("format to use for the output")),
		OPT_BOOL('i', "ignore-case", &icase, N_("sorting and filtering are case insensitive")),
		OPT_END()
	};

	setup_ref_filter_porcelain_msg();

	git_config(git_tag_config, sorting_tail);

	memset(&opt, 0, sizeof(opt));
	memset(&filter, 0, sizeof(filter));
	filter.lines = -1;

	argc = parse_options(argc, argv, prefix, options, git_tag_usage, 0);

	if (keyid) {
		opt.sign = 1;
		set_signing_key(keyid);
	}
	create_tag_object = (opt.sign || annotate || msg.given || msgfile);

	if (!cmdmode) {
		if (argc == 0)
			cmdmode = 'l';
		else if (filter.with_commit || filter.no_commit ||
			 filter.points_at.nr || filter.merge_commit ||
			 filter.lines != -1)
			cmdmode = 'l';
	}

	if ((create_tag_object || force) && (cmdmode != 0))
		usage_with_options(git_tag_usage, options);

	finalize_colopts(&colopts, -1);
	if (cmdmode == 'l' && filter.lines != -1) {
		if (explicitly_enable_column(colopts))
			die(_("--column and -n are incompatible"));
		colopts = 0;
	}
	if (!sorting)
		sorting = ref_default_sorting();
	sorting->ignore_case = icase;
	filter.ignore_case = icase;
	if (cmdmode == 'l') {
		int ret;
		if (column_active(colopts)) {
			struct column_options copts;
			memset(&copts, 0, sizeof(copts));
			copts.padding = 2;
			run_column_filter(colopts, &copts);
		}
		filter.name_patterns = argv;
		ret = list_tags(&filter, sorting, format);
		if (column_active(colopts))
			stop_column_filter();
		return ret;
	}
	if (filter.lines != -1)
		die(_("-n option is only allowed in list mode"));
	if (filter.with_commit)
		die(_("--contains option is only allowed in list mode"));
	if (filter.no_commit)
		die(_("--no-contains option is only allowed in list mode"));
	if (filter.points_at.nr)
		die(_("--points-at option is only allowed in list mode"));
	if (filter.merge_commit)
		die(_("--merged and --no-merged options are only allowed in list mode"));
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
		else {
			if (!strcmp(msgfile, "-")) {
				if (strbuf_read(&buf, 0, 1024) < 0)
					die_errno(_("cannot read '%s'"), msgfile);
			} else {
				if (strbuf_read_file(&buf, msgfile, 1024) < 0)
					die_errno(_("could not open or read '%s'"),
						msgfile);
			}
		}
	}

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
		opt.cleanup_mode = CLEANUP_ALL;
	else if (!strcmp(cleanup_arg, "verbatim"))
		opt.cleanup_mode = CLEANUP_NONE;
	else if (!strcmp(cleanup_arg, "whitespace"))
		opt.cleanup_mode = CLEANUP_SPACE;
	else
		die(_("Invalid cleanup mode %s"), cleanup_arg);

	create_reflog_msg(object, &reflog_msg);

	if (create_tag_object) {
		if (force_sign_annotate && !annotate)
			opt.sign = 1;
		create_tag(object, tag, &buf, &opt, prev, object);
	}

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref.buf, object, prev,
				   create_reflog ? REF_FORCE_CREATE_REFLOG : 0,
				   reflog_msg.buf, &err) ||
	    ref_transaction_commit(transaction, &err))
		die("%s", err.buf);
	ref_transaction_free(transaction);
	if (force && !is_null_sha1(prev) && hashcmp(prev, object))
		printf(_("Updated tag '%s' (was %s)\n"), tag, find_unique_abbrev(prev, DEFAULT_ABBREV));

	strbuf_release(&err);
	strbuf_release(&buf);
	strbuf_release(&ref);
	strbuf_release(&reflog_msg);
	return 0;
}