	hashcpy(obj->idx.sha1, sha1);
	return obj;
}

static int delta_pos_compare(const void *_a, const void *_b)
{
	struct delta_entry *a = *(struct delta_entry **)_a;
	struct delta_entry *b = *(struct delta_entry **)_b;
	return a->obj_no - b->obj_no;
}

static void fix_unresolved_deltas(struct sha1file *f, int nr_unresolved)
{
	struct delta_entry **sorted_by_pos;
	int i, n = 0;

	/*
	 * Since many unresolved deltas may well be themselves base objects
	 * for more unresolved deltas, we really want to include the
	 * smallest number of base objects that would cover as much delta
	 * as possible by picking the
	 * trunc deltas first, allowing for other deltas to resolve without
	 * additional base objects.  Since most base objects are to be found
	 * before deltas depending on them, a good heuristic is to start
	 * resolving deltas in the same order as their position in the pack.
	 */
	sorted_by_pos = xmalloc(nr_unresolved * sizeof(*sorted_by_pos));
	for (i = 0; i < nr_deltas; i++) {
		if (objects[deltas[i].obj_no].real_type != OBJ_REF_DELTA)
			continue;
		sorted_by_pos[n++] = &deltas[i];
	}
	qsort(sorted_by_pos, n, sizeof(*sorted_by_pos), delta_pos_compare);

	for (i = 0; i < n; i++) {
		struct delta_entry *d = sorted_by_pos[i];
		enum object_type type;
		struct base_data *base_obj = alloc_base_data();

		if (objects[d->obj_no].real_type != OBJ_REF_DELTA)
			continue;
		base_obj->data = read_sha1_file(d->base.sha1, &type, &base_obj->size);
		if (!base_obj->data)
			continue;

		if (check_sha1_signature(d->base.sha1, base_obj->data,
				base_obj->size, typename(type)))
			die(_("local object %s is corrupt"), sha1_to_hex(d->base.sha1));
		base_obj->obj = append_obj_to_pack(f, d->base.sha1,
					base_obj->data, base_obj->size, type);
		find_unresolved_deltas(base_obj);
		display_progress(progress, nr_resolved_deltas);
	}
	free(sorted_by_pos);
}
