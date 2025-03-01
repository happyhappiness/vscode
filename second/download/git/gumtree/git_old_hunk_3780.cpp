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
