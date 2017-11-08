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

	if (name_objects)
		fsck_walk_options.object_names =
			xcalloc(1, sizeof(struct decoration));

	git_config(fsck_config, NULL);

	fsck_head_link();
	if (connectivity_only) {
		for_each_loose_object(mark_loose_for_connectivity, NULL, 0);
		for_each_packed_object(mark_packed_for_connectivity, NULL, 0);
	} else {
		fsck_object_dir(get_object_directory());

		prepare_alt_odb();
		for (alt = alt_odb_list; alt; alt = alt->next)
			fsck_object_dir(alt->path);

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
	}

	heads = 0;
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		unsigned char sha1[20];
		if (!get_sha1(arg, sha1)) {
			struct object *obj = lookup_object(sha1);

			if (!obj || !(obj->flags & HAS_OBJ)) {
				error("%s: object missing", sha1_to_hex(sha1));
				errors_found |= ERROR_OBJECT;
				continue;
			}

			obj->used = 1;
			if (name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj, xstrdup(arg));
			mark_object_reachable(obj);
			heads++;
			continue;
		}
		error("invalid parameter: expected sha1, got '%s'", arg);
		errors_found |= ERROR_OBJECT;
	}

	/*
	 * If we've not been given any explicit head information, do the
	 * default ones from .git/refs. We also consider the index file
	 * in this case (ie this implies --cache).
	 */
	if (!argc) {
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
			blob = lookup_blob(active_cache[i]->oid.hash);
			if (!blob)
				continue;
			obj = &blob->object;
			obj->used = 1;
			if (name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj,
					xstrfmt(":%s", active_cache[i]->name));
			mark_object_reachable(obj);
		}
		if (active_cache_tree)
			fsck_cache_tree(active_cache_tree);
	}

	check_connectivity();
	return errors_found;
}