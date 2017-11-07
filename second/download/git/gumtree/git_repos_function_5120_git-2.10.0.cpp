static void collect_one_alternate_ref(const struct ref *ref, void *data)
{
	struct sha1_array *sa = data;
	sha1_array_append(sa, ref->old_oid.hash);
}