static struct base_data *find_unresolved_deltas_1(struct base_data *base,
						  struct base_data *prev_base)
{
	if (base->ref_last == -1 && base->ofs_last == -1) {
		find_ref_delta_children(base->obj->idx.sha1,
					&base->ref_first, &base->ref_last,
					OBJ_REF_DELTA);

		find_ofs_delta_children(base->obj->idx.offset,
					&base->ofs_first, &base->ofs_last,
					OBJ_OFS_DELTA);

		if (base->ref_last == -1 && base->ofs_last == -1) {
			free(base->data);
			return NULL;
		}

		link_base_data(prev_base, base);
	}

	if (base->ref_first <= base->ref_last) {
		struct object_entry *child = objects + ref_deltas[base->ref_first].obj_no;
		struct base_data *result = alloc_base_data();

		if (!compare_and_swap_type(&child->real_type, OBJ_REF_DELTA,
					   base->obj->real_type))
			die("BUG: child->real_type != OBJ_REF_DELTA");

		resolve_delta(child, base, result);
		if (base->ref_first == base->ref_last && base->ofs_last == -1)
			free_base_data(base);

		base->ref_first++;
		return result;
	}

	if (base->ofs_first <= base->ofs_last) {
		struct object_entry *child = objects + ofs_deltas[base->ofs_first].obj_no;
		struct base_data *result = alloc_base_data();

		assert(child->real_type == OBJ_OFS_DELTA);
		child->real_type = base->obj->real_type;
		resolve_delta(child, base, result);
		if (base->ofs_first == base->ofs_last)
			free_base_data(base);

		base->ofs_first++;
		return result;
	}

	unlink_base_data(base);
	return NULL;
}