static void insert_one_alternate_ref(const struct ref *ref, void *unused)
{
	rev_list_insert_ref(NULL, ref->old_sha1, 0, NULL);
}