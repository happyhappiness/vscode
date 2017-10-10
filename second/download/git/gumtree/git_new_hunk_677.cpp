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
