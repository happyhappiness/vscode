static int do_one_ref(struct ref_entry *entry, void *cb_data)
{
	struct ref_entry_cb *data = cb_data;
	struct ref_entry *old_current_ref;
	int retval;

	if (!starts_with(entry->name, data->base))
		return 0;

	if (!(data->flags & DO_FOR_EACH_INCLUDE_BROKEN) &&
	      !ref_resolves_to_object(entry))
		return 0;

	/* Store the old value, in case this is a recursive call: */
	old_current_ref = current_ref;
	current_ref = entry;
	retval = data->fn(entry->name + data->trim, &entry->u.value.oid,
			  entry->flag, data->cb_data);
	current_ref = old_current_ref;
	return retval;
}