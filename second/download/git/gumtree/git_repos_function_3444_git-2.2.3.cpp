static void prepare_ref_index(struct string_list *ref_index, struct ref *ref)
{
	for ( ; ref; ref = ref->next)
		string_list_append_nodup(ref_index, ref->name)->util = ref;

	sort_string_list(ref_index);
}