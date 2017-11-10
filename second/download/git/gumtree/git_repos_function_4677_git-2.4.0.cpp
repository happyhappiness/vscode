static void resolve_delta(struct object_entry *delta_obj,
			  struct base_data *base, struct base_data *result)
{
	void *base_data, *delta_data;

	if (show_stat) {
		delta_obj->delta_depth = base->obj->delta_depth + 1;
		deepest_delta_lock();
		if (deepest_delta < delta_obj->delta_depth)
			deepest_delta = delta_obj->delta_depth;
		deepest_delta_unlock();
	}
	delta_obj->base_object_no = base->obj - objects;
	delta_data = get_data_from_pack(delta_obj);
	base_data = get_base_data(base);
	result->obj = delta_obj;
	result->data = patch_delta(base_data, base->size,
				   delta_data, delta_obj->size, &result->size);
	free(delta_data);
	if (!result->data)
		bad_object(delta_obj->idx.offset, _("failed to apply delta"));
	hash_sha1_file(result->data, result->size,
		       typename(delta_obj->real_type), delta_obj->idx.sha1);
	sha1_object(result->data, NULL, result->size, delta_obj->real_type,
		    delta_obj->idx.sha1);
	counter_lock();
	nr_resolved_deltas++;
	counter_unlock();
}