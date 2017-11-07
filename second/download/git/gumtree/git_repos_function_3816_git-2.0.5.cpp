static int find_copy_in_parent(struct scoreboard *sb,
			       struct origin *target,
			       struct commit *parent,
			       struct origin *porigin,
			       int opt)
{
	struct diff_options diff_opts;
	int i, j;
	int retval;
	struct blame_list *blame_list;
	int num_ents;

	blame_list = setup_blame_list(sb, target, blame_copy_score, &num_ents);
	if (!blame_list)
		return 1; /* nothing remains for this target */

	diff_setup(&diff_opts);
	DIFF_OPT_SET(&diff_opts, RECURSIVE);
	diff_opts.output_format = DIFF_FORMAT_NO_OUTPUT;

	diff_setup_done(&diff_opts);

	/* Try "find copies harder" on new path if requested;
	 * we do not want to use diffcore_rename() actually to
	 * match things up; find_copies_harder is set only to
	 * force diff_tree_sha1() to feed all filepairs to diff_queue,
	 * and this code needs to be after diff_setup_done(), which
	 * usually makes find-copies-harder imply copy detection.
	 */
	if ((opt & PICKAXE_BLAME_COPY_HARDEST)
	    || ((opt & PICKAXE_BLAME_COPY_HARDER)
		&& (!porigin || strcmp(target->path, porigin->path))))
		DIFF_OPT_SET(&diff_opts, FIND_COPIES_HARDER);

	if (is_null_sha1(target->commit->object.sha1))
		do_diff_cache(parent->tree->object.sha1, &diff_opts);
	else
		diff_tree_sha1(parent->tree->object.sha1,
			       target->commit->tree->object.sha1,
			       "", &diff_opts);

	if (!DIFF_OPT_TST(&diff_opts, FIND_COPIES_HARDER))
		diffcore_std(&diff_opts);

	retval = 0;
	while (1) {
		int made_progress = 0;

		for (i = 0; i < diff_queued_diff.nr; i++) {
			struct diff_filepair *p = diff_queued_diff.queue[i];
			struct origin *norigin;
			mmfile_t file_p;
			struct blame_entry this[3];

			if (!DIFF_FILE_VALID(p->one))
				continue; /* does not exist in parent */
			if (S_ISGITLINK(p->one->mode))
				continue; /* ignore git links */
			if (porigin && !strcmp(p->one->path, porigin->path))
				/* find_move already dealt with this path */
				continue;

			norigin = get_origin(sb, parent, p->one->path);
			hashcpy(norigin->blob_sha1, p->one->sha1);
			norigin->mode = p->one->mode;
			fill_origin_blob(&sb->revs->diffopt, norigin, &file_p);
			if (!file_p.ptr)
				continue;

			for (j = 0; j < num_ents; j++) {
				find_copy_in_blob(sb, blame_list[j].ent,
						  norigin, this, &file_p);
				copy_split_if_better(sb, blame_list[j].split,
						     this);
				decref_split(this);
			}
			origin_decref(norigin);
		}

		for (j = 0; j < num_ents; j++) {
			struct blame_entry *split = blame_list[j].split;
			if (split[1].suspect &&
			    blame_copy_score < ent_score(sb, &split[1])) {
				split_blame(sb, split, blame_list[j].ent);
				made_progress = 1;
			}
			else
				blame_list[j].ent->scanned = 1;
			decref_split(split);
		}
		free(blame_list);

		if (!made_progress)
			break;
		blame_list = setup_blame_list(sb, target, blame_copy_score, &num_ents);
		if (!blame_list) {
			retval = 1;
			break;
		}
	}
	reset_scanned_flag(sb);
	diff_flush(&diff_opts);
	free_pathspec(&diff_opts.pathspec);
	return retval;
}