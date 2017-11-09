static void get_object_list(int ac, const char **av)
{
	struct rev_info revs;
	char line[1000];
	int flags = 0;

	init_revisions(&revs, NULL);
	save_commit_buffer = 0;
	setup_revisions(ac, av, &revs, NULL);

	/* make sure shallows are read */
	is_repository_shallow();

	while (fgets(line, sizeof(line), stdin) != NULL) {
		int len = strlen(line);
		if (len && line[len - 1] == '\n')
			line[--len] = 0;
		if (!len)
			break;
		if (*line == '-') {
			if (!strcmp(line, "--not")) {
				flags ^= UNINTERESTING;
				write_bitmap_index = 0;
				continue;
			}
			if (starts_with(line, "--shallow ")) {
				struct object_id oid;
				if (get_oid_hex(line + 10, &oid))
					die("not an SHA-1 '%s'", line + 10);
				register_shallow(&oid);
				use_bitmap_index = 0;
				continue;
			}
			die("not a rev '%s'", line);
		}
		if (handle_revision_arg(line, &revs, flags, REVARG_CANNOT_BE_FILENAME))
			die("bad revision '%s'", line);
	}

	if (use_bitmap_index && !get_object_list_from_bitmap(&revs))
		return;

	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");
	mark_edges_uninteresting(&revs, show_edge);
	traverse_commit_list(&revs, show_commit, show_object, NULL);

	if (unpack_unreachable_expiration) {
		revs.ignore_missing_links = 1;
		if (add_unseen_recent_objects_to_traversal(&revs,
				unpack_unreachable_expiration))
			die("unable to add recent objects");
		if (prepare_revision_walk(&revs))
			die("revision walk setup failed");
		traverse_commit_list(&revs, record_recent_commit,
				     record_recent_object, NULL);
	}

	if (keep_unreachable)
		add_objects_in_unpacked_packs(&revs);
	if (pack_loose_unreachable)
		add_unreachable_loose_objects();
	if (unpack_unreachable)
		loosen_unused_packed_objects(&revs);

	oid_array_clear(&recent_objects);
}