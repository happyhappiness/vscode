static int compare_ref_name(const void *a_, const void *b_)
{
	const char * const*a = a_, * const*b = b_;
	return version_cmp(*a, *b);
}