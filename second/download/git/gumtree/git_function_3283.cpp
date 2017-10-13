static int process_renames(struct merge_options *o,
			   struct string_list *a_renames,
			   struct string_list *b_renames)
{
	int clean_merge = 1, i, j;
	struct string_list a_by_dst = STRING_LIST_INIT_NODUP;
	struct string_list b_by_dst = STRING_LIST_INIT_NODUP;
	const struct rename *sre;

	for (i = 0; i < a_renames->nr; i++) {
		sre = a_renames->items[i].util;
		string_list_insert(&a_by_dst, sre->pair->two->path)->util
			= (void *)sre;
	}
	for (i = 0; i < b_renames->nr; i++) {
		sre = b_renames->items[i].util;
		string_list_insert(&b_by_dst, sre->pair->two->path)->util
			= (void *)sre;
	}

	for (i = 0, j = 0; i < a_renames->nr || j < b_renames->nr;) {
		struct string_list *renames1, *renames2Dst;
		struct rename *ren1 = NULL, *ren2 = NULL;
		const char *branch1, *branch2;
		const char *ren1_src, *ren1_dst;
		struct string_list_item *lookup;

		if (i >= a_renames->nr) {
			ren2 = b_renames->items[j++].util;
		} else if (j >= b_renames->nr) {
			ren1 = a_renames->items[i++].util;
		} else {
			int compare = strcmp(a_renames->items[i].string,
					     b_renames->items[j].string);
			if (compare <= 0)
				ren1 = a_renames->items[i++].util;
			if (compare >= 0)
				ren2 = b_renames->items[j++].util;
		}

		/* TODO: refactor, so that 1/2 are not needed */
		if (ren1) {
			renames1 = a_renames;
			renames2Dst = &b_by_dst;
			branch1 = o->branch1;
			branch2 = o->branch2;
		} else {
			struct rename *tmp;
			renames1 = b_renames;
			renames2Dst = &a_by_dst;
			branch1 = o->branch2;
			branch2 = o->branch1;
			tmp = ren2;
			ren2 = ren1;
			ren1 = tmp;
		}

		if (ren1->processed)
			continue;
		ren1->processed = 1;
		ren1->dst_entry->processed = 1;
		/* BUG: We should only mark src_entry as processed if we
		 * are not dealing with a rename + add-source case.
		 */
		ren1->src_entry->processed = 1;

		ren1_src = ren1->pair->one->path;
		ren1_dst = ren1->pair->two->path;

		if (ren2) {
			/* One file renamed on both sides */
			const char *ren2_src = ren2->pair->one->path;
			const char *ren2_dst = ren2->pair->two->path;
			enum rename_type rename_type;
			if (strcmp(ren1_src, ren2_src) != 0)
				die("ren1_src != ren2_src");
			ren2->dst_entry->processed = 1;
			ren2->processed = 1;
			if (strcmp(ren1_dst, ren2_dst) != 0) {
				rename_type = RENAME_ONE_FILE_TO_TWO;
				clean_merge = 0;
			} else {
				rename_type = RENAME_ONE_FILE_TO_ONE;
				/* BUG: We should only remove ren1_src in
				 * the base stage (think of rename +
				 * add-source cases).
				 */
				remove_file(o, 1, ren1_src, 1);
				update_entry(ren1->dst_entry,
					     ren1->pair->one,
					     ren1->pair->two,
					     ren2->pair->two);
			}
			setup_rename_conflict_info(rename_type,
						   ren1->pair,
						   ren2->pair,
						   branch1,
						   branch2,
						   ren1->dst_entry,
						   ren2->dst_entry,
						   o,
						   NULL,
						   NULL);
		} else if ((lookup = string_list_lookup(renames2Dst, ren1_dst))) {
			/* Two different files renamed to the same thing */
			char *ren2_dst;
			ren2 = lookup->util;
			ren2_dst = ren2->pair->two->path;
			if (strcmp(ren1_dst, ren2_dst) != 0)
				die("ren1_dst != ren2_dst");

			clean_merge = 0;
			ren2->processed = 1;
			/*
			 * BUG: We should only mark src_entry as processed
			 * if we are not dealing with a rename + add-source
			 * case.
			 */
			ren2->src_entry->processed = 1;

			setup_rename_conflict_info(RENAME_TWO_FILES_TO_ONE,
						   ren1->pair,
						   ren2->pair,
						   branch1,
						   branch2,
						   ren1->dst_entry,
						   ren2->dst_entry,
						   o,
						   ren1->src_entry,
						   ren2->src_entry);

		} else {
			/* Renamed in 1, maybe changed in 2 */
			/* we only use sha1 and mode of these */
			struct diff_filespec src_other, dst_other;
			int try_merge;

			/*
			 * unpack_trees loads entries from common-commit
			 * into stage 1, from head-commit into stage 2, and
			 * from merge-commit into stage 3.  We keep track
			 * of which side corresponds to the rename.
			 */
			int renamed_stage = a_renames == renames1 ? 2 : 3;
			int other_stage =   a_renames == renames1 ? 3 : 2;

			/* BUG: We should only remove ren1_src in the base
			 * stage and in other_stage (think of rename +
			 * add-source case).
			 */
			remove_file(o, 1, ren1_src,
				    renamed_stage == 2 || !was_tracked(ren1_src));

			hashcpy(src_other.sha1, ren1->src_entry->stages[other_stage].sha);
			src_other.mode = ren1->src_entry->stages[other_stage].mode;
			hashcpy(dst_other.sha1, ren1->dst_entry->stages[other_stage].sha);
			dst_other.mode = ren1->dst_entry->stages[other_stage].mode;
			try_merge = 0;

			if (sha_eq(src_other.sha1, null_sha1)) {
				setup_rename_conflict_info(RENAME_DELETE,
							   ren1->pair,
							   NULL,
							   branch1,
							   branch2,
							   ren1->dst_entry,
							   NULL,
							   o,
							   NULL,
							   NULL);
			} else if ((dst_other.mode == ren1->pair->two->mode) &&
				   sha_eq(dst_other.sha1, ren1->pair->two->sha1)) {
				/*
				 * Added file on the other side identical to
				 * the file being renamed: clean merge.
				 * Also, there is no need to overwrite the
				 * file already in the working copy, so call
				 * update_file_flags() instead of
				 * update_file().
				 */
				update_file_flags(o,
						  ren1->pair->two->sha1,
						  ren1->pair->two->mode,
						  ren1_dst,
						  1, /* update_cache */
						  0  /* update_wd    */);
			} else if (!sha_eq(dst_other.sha1, null_sha1)) {
				clean_merge = 0;
				try_merge = 1;
				output(o, 1, _("CONFLICT (rename/add): Rename %s->%s in %s. "
				       "%s added in %s"),
				       ren1_src, ren1_dst, branch1,
				       ren1_dst, branch2);
				if (o->call_depth) {
					struct merge_file_info mfi;
					mfi = merge_file_one(o, ren1_dst, null_sha1, 0,
							 ren1->pair->two->sha1, ren1->pair->two->mode,
							 dst_other.sha1, dst_other.mode,
							 branch1, branch2);
					output(o, 1, _("Adding merged %s"), ren1_dst);
					update_file(o, 0, mfi.sha, mfi.mode, ren1_dst);
					try_merge = 0;
				} else {
					char *new_path = unique_path(o, ren1_dst, branch2);
					output(o, 1, _("Adding as %s instead"), new_path);
					update_file(o, 0, dst_other.sha1, dst_other.mode, new_path);
					free(new_path);
				}
			} else
				try_merge = 1;

			if (try_merge) {
				struct diff_filespec *one, *a, *b;
				src_other.path = (char *)ren1_src;

				one = ren1->pair->one;
				if (a_renames == renames1) {
					a = ren1->pair->two;
					b = &src_other;
				} else {
					b = ren1->pair->two;
					a = &src_other;
				}
				update_entry(ren1->dst_entry, one, a, b);
				setup_rename_conflict_info(RENAME_NORMAL,
							   ren1->pair,
							   NULL,
							   branch1,
							   NULL,
							   ren1->dst_entry,
							   NULL,
							   o,
							   NULL,
							   NULL);
			}
		}
	}
	string_list_clear(&a_by_dst, 0);
	string_list_clear(&b_by_dst, 0);

	return clean_merge;
}