static int cmp_ref_by_name(const void *a_, const void *b_)
{
	const struct ref *a = *((const struct ref **)a_);
	const struct ref *b = *((const struct ref **)b_);
	return strcmp(a->name, b->name);
}