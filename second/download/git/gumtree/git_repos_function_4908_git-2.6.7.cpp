int cmd_fsck(int argc, const char **argv, const char *prefix)
{
	int i, heads;
	struct alternate_object_database *alt;

	errors_found = 0;
	check_replace_refs = 0;

	argc = parse_options(argc, argv, prefix, fsck_opts, fsck_usage, 0);

	fsck_walk_options.walk = mark_object;
	fsck_obj_options.walk = mark_used;
	fsck_obj_options.error_func = fsck_error_func;
	if (check_strict)
		fsck_obj_options.strict = 1;

	if (show_progress == -1)
		show_progress = isatty(2);
	if (verbose)
		show_progress = 0;

	if (write_lost_and_found) {
		check_full = 1;
		include_reflogs = 0;
	}

	git_config(fsck_config, NULL);

	fsck_head_link();
	if (!connectivity_only)
		fsck_object_dir(get_object_directory());

	prepare_alt_odb();
	for (alt = alt_odb_list; alt; alt = alt->next) {
		char namebuf[PATH_MAX];
		int namelen = alt->name - alt->base;
		memcpy(namebuf, alt->base, namelen);
		namebuf[namelen - 1] = 0;
		fsck_object_dir(namebuf);
	}

	if (check_full) {
		struct packed_git *p;
		uint32_t total = 0, count = 0;
		struct progress *progress = NULL;

		prepare_packed_git();

		if (show_progress) {
			for (p = packed_git; p; p = p->next) {
				if (open_pack_index(p))
					continue;
				total += p->num_objects;
			}

			progress = start_progress(_("Checking objects"), total);
		}
		for (p = packed_git; p; p = p->next) {
			/* verify gives error messages itself */
			if (verify_pack(p, fsck_obj_buffer,
					progress, count))
				errors_found |= ERROR_PACK;
			count += p->num_objects;
		}
		stop_progress(&progress);
	}

	heads = 0;
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		unsigned char sha1[20];
		if (!get_sha1(arg, sha1)) {
			struct object *obj = lookup_object(sha1);

			/* Error is printed by lookup_object(). */
			if (!obj)
				continue;

			obj->used = 1;
			mark_object_reachable(obj);
			heads++;
			continue;
		}
		error("invalid parameter: expected sha1, got '%s'", arg);
	}

	/*
	 * If we've not been given any explicit head information, do the
	 * default ones from .git/refs. We also consider the index file
	 * in this case (ie this implies --cache).
	 */
	if (!heads) {
		get_default_heads();
		keep_cache_objects = 1;
	}

	if (keep_cache_objects) {
		read_cache();
		for (i = 0; i < active_nr; i++) {
			unsigned int mode;
			struct blob *blob;
			struct object *obj;

			mode = active_cache[i]->ce_mode;
			if (S_ISGITLINK(mode))
				continue;
			blob = lookup_blob(active_cache[i]->sha1);
			if (!blob)
				continue;
			obj = &blob->object;
			obj->used = 1;
			mark_object_reachable(obj);
		}
		if (active_cache_tree)
			fsck_cache_tree(active_cache_tree);
	}

	check_connectivity();
	return errors_found;
}