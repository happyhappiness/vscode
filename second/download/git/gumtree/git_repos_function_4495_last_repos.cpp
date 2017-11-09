struct ref *get_stale_heads(struct refspec *refs, int ref_count, struct ref *fetch_map)
{
	struct ref *ref, *stale_refs = NULL;
	struct string_list ref_names = STRING_LIST_INIT_NODUP;
	struct stale_heads_info info;

	info.ref_names = &ref_names;
	info.stale_refs_tail = &stale_refs;
	info.refs = refs;
	info.ref_count = ref_count;
	for (ref = fetch_map; ref; ref = ref->next)
		string_list_append(&ref_names, ref->name);
	string_list_sort(&ref_names);
	for_each_ref(get_stale_heads_cb, &info);
	string_list_clear(&ref_names, 0);
	return stale_refs;
}