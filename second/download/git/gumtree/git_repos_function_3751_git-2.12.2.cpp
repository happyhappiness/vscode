static int pack_copy_cmp(const char *a, const char *b)
{
	return pack_copy_priority(a) - pack_copy_priority(b);
}