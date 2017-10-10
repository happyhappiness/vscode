		if (!file_exists(path))
			die_errno("cannot stat path '%s'", path);
	}

	revs.disable_stdin = 1;
	setup_revisions(argc, argv, &revs, NULL);
	memset(&sb, 0, sizeof(sb));

	sb.revs = &revs;
	if (!reverse) {
		final_commit_name = prepare_final(&sb);
		sb.commits.compare = compare_commits_by_commit_date;
	}
	else if (contents_from)
		die(_("--contents and --reverse do not blend well."));
	else {
		final_commit_name = prepare_initial(&sb);
		sb.commits.compare = compare_commits_by_reverse_commit_date;
		if (revs.first_parent_only)
			revs.children.name = NULL;
	}

	if (!sb.final) {
		/*
		 * "--not A B -- path" without anything positive;
		 * do not default to HEAD, but use the working tree
		 * or "--contents".
		 */
		setup_work_tree();
		sb.final = fake_working_tree_commit(&sb.revs->diffopt,
						    path, contents_from);
		add_pending_object(&revs, &(sb.final->object), ":");
	}
	else if (contents_from)
		die(_("cannot use --contents with final commit object name"));

	if (reverse && revs.first_parent_only) {
		final_commit = find_single_final(sb.revs, NULL);
		if (!final_commit)
			die(_("--reverse and --first-parent together require specified latest commit"));
	}

	/*
	 * If we have bottom, this will mark the ancestors of the
	 * bottom commits we would reach while traversing as
	 * uninteresting.
	 */
	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));

	if (reverse && revs.first_parent_only) {
		struct commit *c = final_commit;

		sb.revs->children.name = "children";
		while (c->parents &&
		       oidcmp(&c->object.oid, &sb.final->object.oid)) {
			struct commit_list *l = xcalloc(1, sizeof(*l));

			l->item = c;
			if (add_decoration(&sb.revs->children,
					   &c->parents->item->object, l))
				die("BUG: not unique item in first-parent chain");
			c = c->parents->item;
		}

		if (oidcmp(&c->object.oid, &sb.final->object.oid))
			die(_("--reverse --first-parent together require range along first-parent chain"));
	}

	if (is_null_oid(&sb.final->object.oid)) {
		o = sb.final->util;
		sb.final_buf = xmemdupz(o->file.ptr, o->file.size);
		sb.final_buf_size = o->file.size;
	}
	else {
		o = get_origin(&sb, sb.final, path);
		if (fill_blob_sha1_and_mode(o))
			die(_("no such path %s in %s"), path, final_commit_name);

		if (DIFF_OPT_TST(&sb.revs->diffopt, ALLOW_TEXTCONV) &&
		    textconv_object(path, o->mode, &o->blob_oid, 1, (char **) &sb.final_buf,
				    &sb.final_buf_size))
			;
		else
			sb.final_buf = read_sha1_file(o->blob_oid.hash, &type,
						      &sb.final_buf_size);

		if (!sb.final_buf)
			die(_("cannot read blob %s for path %s"),
			    oid_to_hex(&o->blob_oid),
			    path);
	}
	num_read_blob++;
	lno = prepare_lines(&sb);

	if (lno && !range_list.nr)
		string_list_append(&range_list, "1");

	anchor = 1;
	range_set_init(&ranges, range_list.nr);
