static void pass_blame(struct blame_scoreboard *sb, struct blame_origin *origin, int opt)
{
	struct rev_info *revs = sb->revs;
	int i, pass, num_sg;
	struct commit *commit = origin->commit;
	struct commit_list *sg;
	struct blame_origin *sg_buf[MAXSG];
	struct blame_origin *porigin, **sg_origin = sg_buf;
	struct blame_entry *toosmall = NULL;
	struct blame_entry *blames, **blametail = &blames;

	num_sg = num_scapegoats(revs, commit, sb->reverse);
	if (!num_sg)
		goto finish;
	else if (num_sg < ARRAY_SIZE(sg_buf))
		memset(sg_buf, 0, sizeof(sg_buf));
	else
		sg_origin = xcalloc(num_sg, sizeof(*sg_origin));

	/*
	 * The first pass looks for unrenamed path to optimize for
	 * common cases, then we look for renames in the second pass.
	 */
	for (pass = 0; pass < 2 - sb->no_whole_file_rename; pass++) {
		struct blame_origin *(*find)(struct commit *, struct blame_origin *);
		find = pass ? find_rename : find_origin;

		for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct commit *p = sg->item;
			int j, same;

			if (sg_origin[i])
				continue;
			if (parse_commit(p))
				continue;
			porigin = find(p, origin);
			if (!porigin)
				continue;
			if (!oidcmp(&porigin->blob_oid, &origin->blob_oid)) {
				pass_whole_blame(sb, origin, porigin);
				blame_origin_decref(porigin);
				goto finish;
			}
			for (j = same = 0; j < i; j++)
				if (sg_origin[j] &&
				    !oidcmp(&sg_origin[j]->blob_oid, &porigin->blob_oid)) {
					same = 1;
					break;
				}
			if (!same)
				sg_origin[i] = porigin;
			else
				blame_origin_decref(porigin);
		}
	}

	sb->num_commits++;
	for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
	     i < num_sg && sg;
	     sg = sg->next, i++) {
		struct blame_origin *porigin = sg_origin[i];
		if (!porigin)
			continue;
		if (!origin->previous) {
			blame_origin_incref(porigin);
			origin->previous = porigin;
		}
		pass_blame_to_parent(sb, origin, porigin);
		if (!origin->suspects)
			goto finish;
	}

	/*
	 * Optionally find moves in parents' files.
	 */
	if (opt & PICKAXE_BLAME_MOVE) {
		filter_small(sb, &toosmall, &origin->suspects, sb->move_score);
		if (origin->suspects) {
			for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
			     i < num_sg && sg;
			     sg = sg->next, i++) {
				struct blame_origin *porigin = sg_origin[i];
				if (!porigin)
					continue;
				find_move_in_parent(sb, &blametail, &toosmall, origin, porigin);
				if (!origin->suspects)
					break;
			}
		}
	}

	/*
	 * Optionally find copies from parents' files.
	 */
	if (opt & PICKAXE_BLAME_COPY) {
		if (sb->copy_score > sb->move_score)
			filter_small(sb, &toosmall, &origin->suspects, sb->copy_score);
		else if (sb->copy_score < sb->move_score) {
			origin->suspects = blame_merge(origin->suspects, toosmall);
			toosmall = NULL;
			filter_small(sb, &toosmall, &origin->suspects, sb->copy_score);
		}
		if (!origin->suspects)
			goto finish;

		for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct blame_origin *porigin = sg_origin[i];
			find_copy_in_parent(sb, &blametail, &toosmall,
					    origin, sg->item, porigin, opt);
			if (!origin->suspects)
				goto finish;
		}
	}

finish:
	*blametail = NULL;
	distribute_blame(sb, blames);
	/*
	 * prepend toosmall to origin->suspects
	 *
	 * There is no point in sorting: this ends up on a big
	 * unsorted list in the caller anyway.
	 */
	if (toosmall) {
		struct blame_entry **tail = &toosmall;
		while (*tail)
			tail = &(*tail)->next;
		*tail = origin->suspects;
		origin->suspects = toosmall;
	}
	for (i = 0; i < num_sg; i++) {
		if (sg_origin[i]) {
			drop_origin_blob(sg_origin[i]);
			blame_origin_decref(sg_origin[i]);
		}
	}
	drop_origin_blob(origin);
	if (sg_buf != sg_origin)
		free(sg_origin);
}