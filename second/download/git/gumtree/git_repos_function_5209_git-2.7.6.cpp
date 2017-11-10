static int cmp_string_list_util_as_integral(const void *a_, const void *b_)
{
	const struct string_list_item *a = a_, *b = b_;
	return util_as_integral(b) - util_as_integral(a);
}