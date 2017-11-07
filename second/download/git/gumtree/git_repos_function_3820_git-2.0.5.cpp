static void pass_blame(struct scoreboard *sb, struct origin *origin, int opt)
{
	struct rev_info *revs = sb->revs;
	int i, pass, num_sg;
	struct commit *commit = origin->commit;
	struct commit_list *sg;
	struct origin *sg_buf[MAXSG];
	struct origin *porigin, **sg_origin = sg_buf;

	num_sg = num_scapegoats(revs, commit);
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
	for (pass = 0; pass < 2 - no_whole_file_rename; pass++) {
		struct origin *(*find)(struct scoreboard *,
				       struct commit *, struct origin *);
		find = pass ? find_rename : find_origin;

		for (i = 0, sg = first_scapegoat(revs, commit);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct commit *p = sg->item;
			int j, same;

			if (sg_origin[i])
				continue;
			if (parse_commit(p))
				continue;
			porigin = find(sb, p, origin);
			if (!porigin)
				continue;
			if (!hashcmp(porigin->blob_sha1, origin->blob_sha1)) {
				pass_whole_blame(sb, origin, porigin);
				origin_decref(porigin);
				goto finish;
			}
			for (j = same = 0; j < i; j++)
				if (sg_origin[j] &&
				    !hashcmp(sg_origin[j]->blob_sha1,
					     porigin->blob_sha1)) {
					same = 1;
					break;
				}
			if (!same)
				sg_origin[i] = porigin;
			else
				origin_decref(porigin);
		}
	}

	num_commits++;
	for (i = 0, sg = first_scapegoat(revs, commit);
	     i < num_sg && sg;
	     sg = sg->next, i++) {
		struct origin *porigin = sg_origin[i];
		if (!porigin)
			continue;
		if (!origin->previous) {
			origin_incref(porigin);
			origin->previous = porigin;
		}
		if (pass_blame_to_parent(sb, origin, porigin))
			goto finish;
	}

	/*
	 * Optionally find moves in parents' files.
	 */
	if (opt & PICKAXE_BLAME_MOVE)
		for (i = 0, sg = first_scapegoat(revs, commit);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct origin *porigin = sg_origin[i];
			if (!porigin)
				continue;
			if (find_move_in_parent(sb, origin, porigin))
				goto finish;
		}

	/*
	 * Optionally find copies from parents' files.
	 */
	if (opt & PICKAXE_BLAME_COPY)
		for (i = 0, sg = first_scapegoat(revs, commit);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct origin *porigin = sg_origin[i];
			if (find_copy_in_parent(sb, origin, sg->item,
						porigin, opt))
				goto finish;
		}

 finish:
	for (i = 0; i < num_sg; i++) {
		if (sg_origin[i]) {
			drop_origin_blob(sg_origin[i]);
			origin_decref(sg_origin[i]);
		}
	}
	drop_origin_blob(origin);
	if (sg_buf != sg_origin)
		free(sg_origin);
}