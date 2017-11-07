static int name_conflict_fn(struct ref_entry *entry, void *cb_data)
{
	struct name_conflict_cb *data = (struct name_conflict_cb *)cb_data;
	if (data->oldrefname && !strcmp(data->oldrefname, entry->name))
		return 0;
	if (names_conflict(data->refname, entry->name)) {
		data->conflicting_refname = entry->name;
		return 1;
	}
	return 0;
}