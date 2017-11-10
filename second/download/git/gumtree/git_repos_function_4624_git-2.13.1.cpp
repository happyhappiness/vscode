static struct notes_merge_pair *diff_tree_remote(struct notes_merge_options *o,
						 const unsigned char *base,
						 const unsigned char *remote,
						 int *num_changes)
{
	struct diff_options opt;
	struct notes_merge_pair *changes;
	int i, len = 0;

	trace_printf("\tdiff_tree_remote(base = %.7s, remote = %.7s)\n",
	       sha1_to_hex(base), sha1_to_hex(remote));

	diff_setup(&opt);
	DIFF_OPT_SET(&opt, RECURSIVE);
	opt.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_setup_done(&opt);
	diff_tree_sha1(base, remote, "", &opt);
	diffcore_std(&opt);

	changes = xcalloc(diff_queued_diff.nr, sizeof(struct notes_merge_pair));

	for (i = 0; i < diff_queued_diff.nr; i++) {
		struct diff_filepair *p = diff_queued_diff.queue[i];
		struct notes_merge_pair *mp;
		int occupied;
		unsigned char obj[20];

		if (verify_notes_filepair(p, obj)) {
			trace_printf("\t\tCannot merge entry '%s' (%c): "
			       "%.7s -> %.7s. Skipping!\n", p->one->path,
			       p->status, oid_to_hex(&p->one->oid),
			       oid_to_hex(&p->two->oid));
			continue;
		}
		mp = find_notes_merge_pair_pos(changes, len, obj, 1, &occupied);
		if (occupied) {
			/* We've found an addition/deletion pair */
			assert(!hashcmp(mp->obj.hash, obj));
			if (is_null_oid(&p->one->oid)) { /* addition */
				assert(is_null_oid(&mp->remote));
				oidcpy(&mp->remote, &p->two->oid);
			} else if (is_null_oid(&p->two->oid)) { /* deletion */
				assert(is_null_oid(&mp->base));
				oidcpy(&mp->base, &p->one->oid);
			} else
				assert(!"Invalid existing change recorded");
		} else {
			hashcpy(mp->obj.hash, obj);
			oidcpy(&mp->base, &p->one->oid);
			oidcpy(&mp->local, &uninitialized);
			oidcpy(&mp->remote, &p->two->oid);
			len++;
		}
		trace_printf("\t\tStored remote change for %s: %.7s -> %.7s\n",
		       oid_to_hex(&mp->obj), oid_to_hex(&mp->base),
		       oid_to_hex(&mp->remote));
	}
	diff_flush(&opt);
	clear_pathspec(&opt.pathspec);

	*num_changes = len;
	return changes;
}