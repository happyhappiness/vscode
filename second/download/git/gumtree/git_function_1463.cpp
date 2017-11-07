void diffcore_rename(struct diff_options *options)
{
	int detect_rename = options->detect_rename;
	int minimum_score = options->rename_score;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;
	struct diff_score *mx;
	int i, j, rename_count, skip_unmodified = 0;
	int num_create, dst_cnt;
	struct progress *progress = NULL;

	if (!minimum_score)
		minimum_score = DEFAULT_RENAME_SCORE;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (!DIFF_FILE_VALID(p->one)) {
			if (!DIFF_FILE_VALID(p->two))
				continue; /* unmerged */
			else if (options->single_follow &&
				 strcmp(options->single_follow, p->two->path))
				continue; /* not interested */
			else if (!DIFF_OPT_TST(options, RENAME_EMPTY) &&
				 is_empty_blob_sha1(p->two->sha1))
				continue;
			else if (add_rename_dst(p->two) < 0) {
				warning("skipping rename detection, detected"
					" duplicate destination '%s'",
					p->two->path);
				goto cleanup;
			}
		}
		else if (!DIFF_OPT_TST(options, RENAME_EMPTY) &&
			 is_empty_blob_sha1(p->one->sha1))
			continue;
		else if (!DIFF_PAIR_UNMERGED(p) && !DIFF_FILE_VALID(p->two)) {
			/*
			 * If the source is a broken "delete", and
			 * they did not really want to get broken,
			 * that means the source actually stays.
			 * So we increment the "rename_used" score
			 * by one, to indicate ourselves as a user
			 */
			if (p->broken_pair && !p->score)
				p->one->rename_used++;
			register_rename_src(p);
		}
		else if (detect_rename == DIFF_DETECT_COPY) {
			/*
			 * Increment the "rename_used" score by
			 * one, to indicate ourselves as a user.
			 */
			p->one->rename_used++;
			register_rename_src(p);
		}
	}
	if (rename_dst_nr == 0 || rename_src_nr == 0)
		goto cleanup; /* nothing to do */

	/*
	 * We really want to cull the candidates list early
	 * with cheap tests in order to avoid doing deltas.
	 */
	rename_count = find_exact_renames(options);

	/* Did we only want exact renames? */
	if (minimum_score == MAX_SCORE)
		goto cleanup;

	/*
	 * Calculate how many renames are left (but all the source
	 * files still remain as options for rename/copies!)
	 */
	num_create = (rename_dst_nr - rename_count);

	/* All done? */
	if (!num_create)
		goto cleanup;

	switch (too_many_rename_candidates(num_create, options)) {
	case 1:
		goto cleanup;
	case 2:
		options->degraded_cc_to_c = 1;
		skip_unmodified = 1;
		break;
	default:
		break;
	}

	if (options->show_rename_progress) {
		progress = start_progress_delay(
				_("Performing inexact rename detection"),
				rename_dst_nr * rename_src_nr, 50, 1);
	}

	mx = xcalloc(num_create * NUM_CANDIDATE_PER_DST, sizeof(*mx));
	for (dst_cnt = i = 0; i < rename_dst_nr; i++) {
		struct diff_filespec *two = rename_dst[i].two;
		struct diff_score *m;

		if (rename_dst[i].pair)
			continue; /* dealt with exact match already. */

		m = &mx[dst_cnt * NUM_CANDIDATE_PER_DST];
		for (j = 0; j < NUM_CANDIDATE_PER_DST; j++)
			m[j].dst = -1;

		for (j = 0; j < rename_src_nr; j++) {
			struct diff_filespec *one = rename_src[j].p->one;
			struct diff_score this_src;

			if (skip_unmodified &&
			    diff_unmodified_pair(rename_src[j].p))
				continue;

			this_src.score = estimate_similarity(one, two,
							     minimum_score);
			this_src.name_score = basename_same(one, two);
			this_src.dst = i;
			this_src.src = j;
			record_if_better(m, &this_src);
			/*
			 * Once we run estimate_similarity,
			 * We do not need the text anymore.
			 */
			diff_free_filespec_blob(one);
			diff_free_filespec_blob(two);
		}
		dst_cnt++;
		display_progress(progress, (i+1)*rename_src_nr);
	}
	stop_progress(&progress);

	/* cost matrix sorted by most to least similar pair */
	qsort(mx, dst_cnt * NUM_CANDIDATE_PER_DST, sizeof(*mx), score_compare);

	rename_count += find_renames(mx, dst_cnt, minimum_score, 0);
	if (detect_rename == DIFF_DETECT_COPY)
		rename_count += find_renames(mx, dst_cnt, minimum_score, 1);
	free(mx);

 cleanup:
	/* At this point, we have found some renames and copies and they
	 * are recorded in rename_dst.  The original list is still in *q.
	 */
	DIFF_QUEUE_CLEAR(&outq);
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		struct diff_filepair *pair_to_free = NULL;

		if (DIFF_PAIR_UNMERGED(p)) {
			diff_q(&outq, p);
		}
		else if (!DIFF_FILE_VALID(p->one) && DIFF_FILE_VALID(p->two)) {
			/*
			 * Creation
			 *
			 * We would output this create record if it has
			 * not been turned into a rename/copy already.
			 */
			struct diff_rename_dst *dst = locate_rename_dst(p->two);
			if (dst && dst->pair) {
				diff_q(&outq, dst->pair);
				pair_to_free = p;
			}
			else
				/* no matching rename/copy source, so
				 * record this as a creation.
				 */
				diff_q(&outq, p);
		}
		else if (DIFF_FILE_VALID(p->one) && !DIFF_FILE_VALID(p->two)) {
			/*
			 * Deletion
			 *
			 * We would output this delete record if:
			 *
			 * (1) this is a broken delete and the counterpart
			 *     broken create remains in the output; or
			 * (2) this is not a broken delete, and rename_dst
			 *     does not have a rename/copy to move p->one->path
			 *     out of existence.
			 *
			 * Otherwise, the counterpart broken create
			 * has been turned into a rename-edit; or
			 * delete did not have a matching create to
			 * begin with.
			 */
			if (DIFF_PAIR_BROKEN(p)) {
				/* broken delete */
				struct diff_rename_dst *dst = locate_rename_dst(p->one);
				if (dst && dst->pair)
					/* counterpart is now rename/copy */
					pair_to_free = p;
			}
			else {
				if (p->one->rename_used)
					/* this path remains */
					pair_to_free = p;
			}

			if (pair_to_free)
				;
			else
				diff_q(&outq, p);
		}
		else if (!diff_unmodified_pair(p))
			/* all the usual ones need to be kept */
			diff_q(&outq, p);
		else
			/* no need to keep unmodified pairs */
			pair_to_free = p;

		if (pair_to_free)
			diff_free_filepair(pair_to_free);
	}
	diff_debug_queue("done copying original", &outq);

	free(q->queue);
	*q = outq;
	diff_debug_queue("done collapsing", q);

	for (i = 0; i < rename_dst_nr; i++)
		free_filespec(rename_dst[i].two);

	free(rename_dst);
	rename_dst = NULL;
	rename_dst_nr = rename_dst_alloc = 0;
	free(rename_src);
	rename_src = NULL;
	rename_src_nr = rename_src_alloc = 0;
	return;
}