static int nonmatching_ref_fn(struct ref_entry *entry, void *vdata)
{
	struct nonmatching_ref_data *data = vdata;

	if (entry_matches(entry, data->skip))
		return 0;

	data->found = entry;
	return 1;
}