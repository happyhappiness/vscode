int run_diff_files(struct rev_info *revs, unsigned int option)
{
	int entries, i;
	int diff_unmerged_stage = revs->max_count;
	unsigned ce_option = ((option & DIFF_RACY_IS_MODIFIED)
			      ? CE_MATCH_RACY_IS_DIRTY : 0);

	diff_set_mnemonic_prefix(&revs->diffopt, "i/", "w/");

	if (diff_unmerged_stage < 0)
		diff_unmerged_stage = 2;
	entries = active_nr;
	for (i = 0; i < entries; i++) {
		unsigned int oldmode, newmode;
		struct cache_entry *ce = active_cache[i];
		int changed;
		unsigned dirty_submodule = 0;
		const unsigned char *old_sha1, *new_sha1;

		if (diff_can_quit_early(&revs->diffopt))
			break;

		if (!ce_path_match(ce, &revs->prune_data, NULL))
			continue;

		if (ce_stage(ce)) {
			struct combine_diff_path *dpath;
			struct diff_filepair *pair;
			unsigned int wt_mode = 0;
			int num_compare_stages = 0;
			size_t path_len;
			struct stat st;

			path_len = ce_namelen(ce);

			dpath = xmalloc(combine_diff_path_size(5, path_len));
			dpath->path = (char *) &(dpath->parent[5]);

			dpath->next = NULL;
			memcpy(dpath->path, ce->name, path_len);
			dpath->path[path_len] = '\0';
			hashclr(dpath->sha1);
			memset(&(dpath->parent[0]), 0,
			       sizeof(struct combine_diff_parent)*5);

			changed = check_removed(ce, &st);
			if (!changed)
				wt_mode = ce_mode_from_stat(ce, st.st_mode);
			else {
				if (changed < 0) {
					perror(ce->name);
					continue;
				}
				wt_mode = 0;
			}
			dpath->mode = wt_mode;

			while (i < entries) {
				struct cache_entry *nce = active_cache[i];
				int stage;

				if (strcmp(ce->name, nce->name))
					break;

				/* Stage #2 (ours) is the first parent,
				 * stage #3 (theirs) is the second.
				 */
				stage = ce_stage(nce);
				if (2 <= stage) {
					int mode = nce->ce_mode;
					num_compare_stages++;
					hashcpy(dpath->parent[stage-2].sha1, nce->sha1);
					dpath->parent[stage-2].mode = ce_mode_from_stat(nce, mode);
					dpath->parent[stage-2].status =
						DIFF_STATUS_MODIFIED;
				}

				/* diff against the proper unmerged stage */
				if (stage == diff_unmerged_stage)
					ce = nce;
				i++;
			}
			/*
			 * Compensate for loop update
			 */
			i--;

			if (revs->combine_merges && num_compare_stages == 2) {
				show_combined_diff(dpath, 2,
						   revs->dense_combined_merges,
						   revs);
				free(dpath);
				continue;
			}
			free(dpath);
			dpath = NULL;

			/*
			 * Show the diff for the 'ce' if we found the one
			 * from the desired stage.
			 */
			pair = diff_unmerge(&revs->diffopt, ce->name);
			if (wt_mode)
				pair->two->mode = wt_mode;
			if (ce_stage(ce) != diff_unmerged_stage)
				continue;
		}

		if (ce_uptodate(ce) || ce_skip_worktree(ce))
			continue;

		/* If CE_VALID is set, don't look at workdir for file removal */
		if (ce->ce_flags & CE_VALID) {
			changed = 0;
			newmode = ce->ce_mode;
		} else {
			struct stat st;

			changed = check_removed(ce, &st);
			if (changed) {
				if (changed < 0) {
					perror(ce->name);
					continue;
				}
				diff_addremove(&revs->diffopt, '-', ce->ce_mode,
					       ce->sha1, !is_null_sha1(ce->sha1),
					       ce->name, 0);
				continue;
			}

			changed = match_stat_with_submodule(&revs->diffopt, ce, &st,
							    ce_option, &dirty_submodule);
			newmode = ce_mode_from_stat(ce, st.st_mode);
		}

		if (!changed && !dirty_submodule) {
			ce_mark_uptodate(ce);
			if (!DIFF_OPT_TST(&revs->diffopt, FIND_COPIES_HARDER))
				continue;
		}
		oldmode = ce->ce_mode;
		old_sha1 = ce->sha1;
		new_sha1 = changed ? null_sha1 : ce->sha1;
		diff_change(&revs->diffopt, oldmode, newmode,
			    old_sha1, new_sha1,
			    !is_null_sha1(old_sha1),
			    !is_null_sha1(new_sha1),
			    ce->name, 0, dirty_submodule);

	}
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}