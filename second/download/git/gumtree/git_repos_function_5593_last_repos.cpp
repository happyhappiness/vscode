static int compare_ofs_delta_entry(const void *a, const void *b)
{
	const struct ofs_delta_entry *delta_a = a;
	const struct ofs_delta_entry *delta_b = b;

	return delta_a->offset < delta_b->offset ? -1 :
	       delta_a->offset > delta_b->offset ?  1 :
	       0;
}