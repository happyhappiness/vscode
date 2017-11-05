static int sort_by_version(const void *a_, const void *b_)
{
	const struct string_list_item *a = a_;
	const struct string_list_item *b = b_;
	return versioncmp(a->string, b->string);
}