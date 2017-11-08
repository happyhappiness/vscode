struct ref *get_local_heads(void)
{
	struct ref *local_refs = NULL, **local_tail = &local_refs;

	for_each_ref(one_local_ref, &local_tail);
	return local_refs;
}