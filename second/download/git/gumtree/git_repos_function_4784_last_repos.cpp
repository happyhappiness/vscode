static void diff_tree_local(struct notes_merge_options *o,
			    struct notes_merge_pair *changes, int len,
			    const struct object_id *base,
			    const struct object_id *local)
{
	struct diff_options opt;
	int i;

	trace_printf("\tdiff_tree_local(len = %i, base = %.7s, local = %.7s)\n",
	       len, oid_to_hex(base), oid_to_hex(local));

	diff_setup(&opt);
	DIFF_OPT_SET(&opt, RECURSIVE);
	opt.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_setup_done(&opt);
	diff_tree_oid(base, local, "", &opt);
	diffcore_std(&opt);

	for (i = 0; i < diff_queued_diff.nr; i++) {
		struct diff_filepair *p = diff_queued_diff.queue[i];
		struct notes_merge_pair *mp;
		int match;
		struct object_id obj;

		if (verify_notes_filepair(p, &obj)) {
			trace_printf("\t\tCannot merge entry '%s' (%c): "
			       "%.7s -> %.7s. Skipping!\n", p->one->path,
			       p->status, oid_to_hex(&p->one->oid),
			       oid_to_hex(&p->two->oid));
			continue;
		}
		mp = find_notes_merge_pair_pos(changes, len, &obj, 0, &match);
		if (!match) {
			trace_printf("\t\tIgnoring local-only change for %s: "
			       "%.7s -> %.7s\n", oid_to_hex(&obj),
			       oid_to_hex(&p->one->oid),
			       oid_to_hex(&p->two->oid));
			continue;
		}

		assert(!oidcmp(&mp->obj, &obj));
		if (is_null_oid(&p->two->oid)) { /* deletion */
			/*
			 * Either this is a true deletion (1), or it is part
			 * of an A/D pair (2), or D/A pair (3):
			 *
			 * (1) mp->local is uninitialized; set it to null_sha1
			 * (2) mp->local is not uninitialized; don't touch it
			 * (3) mp->local is uninitialized; set it to null_sha1
			 *     (will be overwritten by following addition)
			 */
			if (!oidcmp(&mp->local, &uninitialized))
				oidclr(&mp->local);
		} else if (is_null_oid(&p->one->oid)) { /* addition */
			/*
			 * Either this is a true addition (1), or it is part
			 * of an A/D pair (2), or D/A pair (3):
			 *
			 * (1) mp->local is uninitialized; set to p->two->sha1
			 * (2) mp->local is uninitialized; set to p->two->sha1
			 * (3) mp->local is null_sha1;     set to p->two->sha1
			 */
			assert(is_null_oid(&mp->local) ||
			       !oidcmp(&mp->local, &uninitialized));
			oidcpy(&mp->local, &p->two->oid);
		} else { /* modification */
			/*
			 * This is a true modification. p->one->sha1 shall
			 * match mp->base, and mp->local shall be uninitialized.
			 * Set mp->local to p->two->sha1.
			 */
			assert(!oidcmp(&p->one->oid, &mp->base));
			assert(!oidcmp(&mp->local, &uninitialized));
			oidcpy(&mp->local, &p->two->oid);
		}
		trace_printf("\t\tStored local change for %s: %.7s -> %.7s\n",
		       oid_to_hex(&mp->obj), oid_to_hex(&mp->base),
		       oid_to_hex(&mp->local));
	}
	diff_flush(&opt);
	clear_pathspec(&opt.pathspec);
}