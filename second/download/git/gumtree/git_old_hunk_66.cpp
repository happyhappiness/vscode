
	for (i = 0; i < 3; i++)
		origin_decref(split[i].suspect);
}

/*
 * Helper for blame_chunk().  blame_entry e is known to overlap with
 * the patch hunk; split it and pass blame to the parent.
 */
static void blame_overlap(struct scoreboard *sb, struct blame_entry *e,
			  int tlno, int plno, int same,
			  struct origin *parent)
{
	struct blame_entry split[3];

	split_overlap(split, e, tlno, plno, same, parent);
	if (split[1].suspect)
		split_blame(sb, split, e);
	decref_split(split);
}

/*
 * Find the line number of the last line the target is suspected for.
 */
static int find_last_in_target(struct scoreboard *sb, struct origin *target)
{
	struct blame_entry *e;
	int last_in_target = -1;

	for (e = sb->ent; e; e = e->next) {
		if (e->guilty || e->suspect != target)
			continue;
		if (last_in_target < e->s_lno + e->num_lines)
			last_in_target = e->s_lno + e->num_lines;
	}
	return last_in_target;
}

/*
 * Process one hunk from the patch between the current suspect for
 * blame_entry e and its parent.  Find and split the overlap, and
 * pass blame to the overlapping part to the parent.
 */
static void blame_chunk(struct scoreboard *sb,
			int tlno, int plno, int same,
			struct origin *target, struct origin *parent)
{
	struct blame_entry *e;

	for (e = sb->ent; e; e = e->next) {
		if (e->guilty || e->suspect != target)
			continue;
		if (same <= e->s_lno)
			continue;
		if (tlno < e->s_lno + e->num_lines)
			blame_overlap(sb, e, tlno, plno, same, parent);
	}
}

struct blame_chunk_cb_data {
	struct scoreboard *sb;
	struct origin *target;
	struct origin *parent;
	long plno;
	long tlno;
};

static int blame_chunk_cb(long start_a, long count_a,
			  long start_b, long count_b, void *data)
{
	struct blame_chunk_cb_data *d = data;
	blame_chunk(d->sb, d->tlno, d->plno, start_b, d->target, d->parent);
	d->plno = start_a + count_a;
	d->tlno = start_b + count_b;
	return 0;
}

/*
 * We are looking at the origin 'target' and aiming to pass blame
 * for the lines it is suspected to its parent.  Run diff to find
 * which lines came from parent and pass blame for them.
 */
static int pass_blame_to_parent(struct scoreboard *sb,
				struct origin *target,
				struct origin *parent)
{
	int last_in_target;
	mmfile_t file_p, file_o;
	struct blame_chunk_cb_data d;

	memset(&d, 0, sizeof(d));
	d.sb = sb; d.target = target; d.parent = parent;
	last_in_target = find_last_in_target(sb, target);
	if (last_in_target < 0)
		return 1; /* nothing remains for this target */

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p);
	fill_origin_blob(&sb->revs->diffopt, target, &file_o);
	num_get_patch++;

	diff_hunks(&file_p, &file_o, 0, blame_chunk_cb, &d);
	/* The rest (i.e. anything after tlno) are the same as the parent */
	blame_chunk(sb, d.tlno, d.plno, last_in_target, target, parent);

	return 0;
}

/*
 * The lines in blame_entry after splitting blames many times can become
 * very small and trivial, and at some point it becomes pointless to
 * blame the parents.  E.g. "\t\t}\n\t}\n\n" appears everywhere in any
