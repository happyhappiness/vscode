static struct origin *find_origin(struct scoreboard *sb,
				  struct commit *parent,
				  struct origin *origin)
{
	struct origin *porigin = NULL;
	struct diff_options diff_opts;
	const char *paths[2];

	if (parent->util) {
		/*
		 * Each commit object can cache one origin in that
		 * commit.  This is a freestanding copy of origin and
		 * not refcounted.
		 */
		struct origin *cached = parent->util;
		if (!strcmp(cached->path, origin->path)) {
			/*
			 * The same path between origin and its parent
			 * without renaming -- the most common case.
			 */
			porigin = get_origin(sb, parent, cached->path);

			/*
			 * If the origin was newly created (i.e. get_origin
			 * would call make_origin if none is found in the
			 * scoreboard), it does not know the blob_sha1/mode,
			 * so copy it.  Otherwise porigin was in the
			 * scoreboard and already knows blob_sha1/mode.
			 */
			if (porigin->refcnt == 1) {
				hashcpy(porigin->blob_sha1, cached->blob_sha1);
				porigin->mode = cached->mode;
			}
			return porigin;
		}
		/* otherwise it was not very useful; free it */
		free(parent->util);
		parent->util = NULL;
	}

	/* See if the origin->path is different between parent
	 * and origin first.  Most of the time they are the
	 * same and diff-tree is fairly efficient about this.
	 */
	diff_setup(&diff_opts);
	DIFF_OPT_SET(&diff_opts, RECURSIVE);
	diff_opts.detect_rename = 0;
	diff_opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	paths[0] = origin->path;
	paths[1] = NULL;

	parse_pathspec(&diff_opts.pathspec,
		       PATHSPEC_ALL_MAGIC & ~PATHSPEC_LITERAL,
		       PATHSPEC_LITERAL_PATH, "", paths);
	diff_setup_done(&diff_opts);

	if (is_null_sha1(origin->commit->object.sha1))
		do_diff_cache(parent->tree->object.sha1, &diff_opts);
	else
		diff_tree_sha1(parent->tree->object.sha1,
			       origin->commit->tree->object.sha1,
			       "", &diff_opts);
	diffcore_std(&diff_opts);

	if (!diff_queued_diff.nr) {
		/* The path is the same as parent */
		porigin = get_origin(sb, parent, origin->path);
		hashcpy(porigin->blob_sha1, origin->blob_sha1);
		porigin->mode = origin->mode;
	} else {
		/*
		 * Since origin->path is a pathspec, if the parent
		 * commit had it as a directory, we will see a whole
		 * bunch of deletion of files in the directory that we
		 * do not care about.
		 */
		int i;
		struct diff_filepair *p = NULL;
		for (i = 0; i < diff_queued_diff.nr; i++) {
			const char *name;
			p = diff_queued_diff.queue[i];
			name = p->one->path ? p->one->path : p->two->path;
			if (!strcmp(name, origin->path))
				break;
		}
		if (!p)
			die("internal error in blame::find_origin");
		switch (p->status) {
		default:
			die("internal error in blame::find_origin (%c)",
			    p->status);
		case 'M':
			porigin = get_origin(sb, parent, origin->path);
			hashcpy(porigin->blob_sha1, p->one->sha1);
			porigin->mode = p->one->mode;
			break;
		case 'A':
		case 'T':
			/* Did not exist in parent, or type changed */
			break;
		}
	}
	diff_flush(&diff_opts);
	free_pathspec(&diff_opts.pathspec);
	if (porigin) {
		/*
		 * Create a freestanding copy that is not part of
		 * the refcounted origin found in the scoreboard, and
		 * cache it in the commit.
		 */
		struct origin *cached;

		cached = make_origin(porigin->commit, porigin->path);
		hashcpy(cached->blob_sha1, porigin->blob_sha1);
		cached->mode = porigin->mode;
		parent->util = cached;
	}
	return porigin;
}