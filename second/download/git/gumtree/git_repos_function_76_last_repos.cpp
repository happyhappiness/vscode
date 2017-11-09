static struct string_list guess_refs(const char *ref)
{
	struct similar_ref_cb ref_cb;
	struct string_list similar_refs = STRING_LIST_INIT_NODUP;

	ref_cb.base_ref = ref;
	ref_cb.similar_refs = &similar_refs;
	for_each_ref(append_similar_ref, &ref_cb);
	return similar_refs;
}