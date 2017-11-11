void assign_shallow_commits_to_refs(struct shallow_info *info,
				    uint32_t **used, int *ref_status)
{
	unsigned char (*sha1)[20] = info->shallow->sha1;
	struct sha1_array *ref = info->ref;
	unsigned int i, nr;
	int *shallow, nr_shallow = 0;
	struct paint_info pi;

	trace_printf_key(&trace_shallow, "shallow: assign_shallow_commits_to_refs\n");
	shallow = xmalloc(sizeof(*shallow) * (info->nr_ours + info->nr_theirs));
	for (i = 0; i < info->nr_ours; i++)
		shallow[nr_shallow++] = info->ours[i];
	for (i = 0; i < info->nr_theirs; i++)
		shallow[nr_shallow++] = info->theirs[i];

	/*
	 * Prepare the commit graph to track what refs can reach what
	 * (new) shallow commits.
	 */
	nr = get_max_object_index();
	for (i = 0; i < nr; i++) {
		struct object *o = get_indexed_object(i);
		if (!o || o->type != OBJ_COMMIT)
			continue;

		o->flags &= ~(UNINTERESTING | BOTTOM | SEEN);
	}

	memset(&pi, 0, sizeof(pi));
	init_ref_bitmap(&pi.ref_bitmap);
	pi.nr_bits = ref->nr;

	/*
	 * "--not --all" to cut short the traversal if new refs
	 * connect to old refs. If not (e.g. force ref updates) it'll
	 * have to go down to the current shallow commits.
	 */
	head_ref(mark_uninteresting, NULL);
	for_each_ref(mark_uninteresting, NULL);

	/* Mark potential bottoms so we won't go out of bound */
	for (i = 0; i < nr_shallow; i++) {
		struct commit *c = lookup_commit(sha1[shallow[i]]);
		c->object.flags |= BOTTOM;
	}

	for (i = 0; i < ref->nr; i++)
		paint_down(&pi, ref->sha1[i], i);

	if (used) {
		int bitmap_size = ((pi.nr_bits + 31) / 32) * sizeof(uint32_t);
		memset(used, 0, sizeof(*used) * info->shallow->nr);
		for (i = 0; i < nr_shallow; i++) {
			const struct commit *c = lookup_commit(sha1[shallow[i]]);
			uint32_t **map = ref_bitmap_at(&pi.ref_bitmap, c);
			if (*map)
				used[shallow[i]] = xmemdupz(*map, bitmap_size);
		}
		/*
		 * unreachable shallow commits are not removed from
		 * "ours" and "theirs". The user is supposed to run
		 * step 7 on every ref separately and not trust "ours"
		 * and "theirs" any more.
		 */
	} else
		post_assign_shallow(info, &pi.ref_bitmap, ref_status);

	clear_ref_bitmap(&pi.ref_bitmap);
	for (i = 0; i < pi.slab_count; i++)
		free(pi.slab[i]);
	free(pi.slab);
	free(shallow);
}