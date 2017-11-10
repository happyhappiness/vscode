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
	if (!index_name && pack_name) {
		size_t len;
		if (!strip_suffix(pack_name, ".pack", &len))
			die(_("packfile name '%s' does not end with '.pack'"),
			    pack_name);
		strbuf_add(&index_name_buf, pack_name, len);
		strbuf_addstr(&index_name_buf, ".idx");
		index_name = index_name_buf.buf;
	}
	if (keep_msg && !keep_name && pack_name) {
		size_t len;
		if (!strip_suffix(pack_name, ".pack", &len))
			die(_("packfile name '%s' does not end with '.pack'"),
			    pack_name);
		strbuf_add(&keep_name_buf, pack_name, len);
		strbuf_addstr(&keep_name_buf, ".idx");
		keep_name = keep_name_buf.buf;
	}
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
	objects = xcalloc(st_add(nr_objects, 1), sizeof(struct object_entry));
	if (show_stat)
		obj_stat = xcalloc(st_add(nr_objects, 1), sizeof(struct object_stat));
	ofs_deltas = xcalloc(nr_objects, sizeof(struct ofs_delta_entry));
	parse_pack_objects(pack_sha1);
	resolve_deltas();
	conclude_pack(fix_thin_pack, curr_pack, pack_sha1);
	free(ofs_deltas);
	free(ref_deltas);
	if (strict)
		foreign_nr = check_objects();

	if (show_stat)
		show_pack_info(stat_only);

	ALLOC_ARRAY(idx_objects, nr_objects);
	for (i = 0; i < nr_objects; i++)
		idx_objects[i] = &objects[i].idx;
	curr_index = write_idx_file(index_name, idx_objects, nr_objects, &opts, pack_sha1);
	free(idx_objects);

	if (!verify)
		final(pack_name, curr_pack,
		      index_name, curr_index,
		      keep_name, keep_msg,
		      pack_sha1);
	else
		close(input_fd);
	free(objects);
	strbuf_release(&index_name_buf);
	strbuf_release(&keep_name_buf);
	if (pack_name == NULL)
		free((void *) curr_pack);
	if (index_name == NULL)
		free((void *) curr_index);

	/*
	 * Let the caller know this pack is not self contained
	 */
	if (check_self_contained_and_connected && foreign_nr)
		return 1;

	return 0;
}