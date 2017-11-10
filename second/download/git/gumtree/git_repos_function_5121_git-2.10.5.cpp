int cmd_index_pack(int argc, const char **argv, const char *prefix)
{
	int i, fix_thin_pack = 0, verify = 0, stat_only = 0;
	const char *curr_index;
	const char *index_name = NULL, *pack_name = NULL;
	const char *keep_name = NULL, *keep_msg = NULL;
	struct strbuf index_name_buf = STRBUF_INIT,
		      keep_name_buf = STRBUF_INIT;
	struct pack_idx_entry **idx_objects;
	struct pack_idx_option opts;
	unsigned char pack_sha1[20];
	unsigned foreign_nr = 1;	/* zero is a "good" value, assume bad */
	int report_end_of_input = 0;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(index_pack_usage);

	check_replace_refs = 0;
	fsck_options.walk = mark_link;

	reset_pack_idx_option(&opts);
	git_config(git_index_pack_config, &opts);
	if (prefix && chdir(prefix))
		die(_("Cannot come back to cwd"));

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];

		if (*arg == '-') {
			if (!strcmp(arg, "--stdin")) {
				from_stdin = 1;
			} else if (!strcmp(arg, "--fix-thin")) {
				fix_thin_pack = 1;
			} else if (!strcmp(arg, "--strict")) {
				strict = 1;
				do_fsck_object = 1;
			} else if (skip_prefix(arg, "--strict=", &arg)) {
				strict = 1;
				do_fsck_object = 1;
				fsck_set_msg_types(&fsck_options, arg);
			} else if (!strcmp(arg, "--check-self-contained-and-connected")) {
				strict = 1;
				check_self_contained_and_connected = 1;
			} else if (!strcmp(arg, "--verify")) {
				verify = 1;
			} else if (!strcmp(arg, "--verify-stat")) {
				verify = 1;
				show_stat = 1;
			} else if (!strcmp(arg, "--verify-stat-only")) {
				verify = 1;
				show_stat = 1;
				stat_only = 1;
			} else if (!strcmp(arg, "--keep")) {
				keep_msg = "";
			} else if (starts_with(arg, "--keep=")) {
				keep_msg = arg + 7;
			} else if (starts_with(arg, "--threads=")) {
				char *end;
				nr_threads = strtoul(arg+10, &end, 0);
				if (!arg[10] || *end || nr_threads < 0)
					usage(index_pack_usage);
#ifdef NO_PTHREADS
				if (nr_threads != 1)
					warning(_("no threads support, "
						  "ignoring %s"), arg);
				nr_threads = 1;
#endif
			} else if (starts_with(arg, "--pack_header=")) {
				struct pack_header *hdr;
				char *c;

				hdr = (struct pack_header *)input_buffer;
				hdr->hdr_signature = htonl(PACK_SIGNATURE);
				hdr->hdr_version = htonl(strtoul(arg + 14, &c, 10));
				if (*c != ',')
					die(_("bad %s"), arg);
				hdr->hdr_entries = htonl(strtoul(c + 1, &c, 10));
				if (*c)
					die(_("bad %s"), arg);
				input_len = sizeof(*hdr);
			} else if (!strcmp(arg, "-v")) {
				verbose = 1;
			} else if (!strcmp(arg, "--show-resolving-progress")) {
				show_resolving_progress = 1;
			} else if (!strcmp(arg, "--report-end-of-input")) {
				report_end_of_input = 1;
			} else if (!strcmp(arg, "-o")) {
				if (index_name || (i+1) >= argc)
					usage(index_pack_usage);
				index_name = argv[++i];
			} else if (starts_with(arg, "--index-version=")) {
				char *c;
				opts.version = strtoul(arg + 16, &c, 10);
				if (opts.version > 2)
					die(_("bad %s"), arg);
				if (*c == ',')
					opts.off32_limit = strtoul(c+1, &c, 0);
				if (*c || opts.off32_limit & 0x80000000)
					die(_("bad %s"), arg);
			} else
				usage(index_pack_usage);
			continue;
		}

		if (pack_name)
			usage(index_pack_usage);
		pack_name = arg;
	}

	if (!pack_name && !from_stdin)
		usage(index_pack_usage);
	if (fix_thin_pack && !from_stdin)
		die(_("--fix-thin cannot be used without --stdin"));
	if (!index_name && pack_name)
		index_name = derive_filename(pack_name, ".idx", &index_name_buf);
	if (keep_msg && !keep_name && pack_name)
		keep_name = derive_filename(pack_name, ".keep", &keep_name_buf);

	if (verify) {
		if (!index_name)
			die(_("--verify with no packfile name given"));
		read_idx_option(&opts, index_name);
		opts.flags |= WRITE_IDX_VERIFY | WRITE_IDX_STRICT;
	}
	if (strict)
		opts.flags |= WRITE_IDX_STRICT;

#ifndef NO_PTHREADS
	if (!nr_threads) {
		nr_threads = online_cpus();
		/* An experiment showed that more threads does not mean faster */
		if (nr_threads > 3)
			nr_threads = 3;
	}
#endif

	curr_pack = open_pack_file(pack_name);
	parse_pack_header();
	objects = x