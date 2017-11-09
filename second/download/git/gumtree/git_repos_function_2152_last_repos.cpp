static int cmp_items(const void *a, const void *b, void *ctx)
{
	compare_strings_fn cmp = ctx;
	const struct string_list_item *one = a;
	const struct string_list_item *two = b;
	return cmp(one->string, two->string);
}