static int compare_ref_delta_entry(const void *a, const void *b)
{
	const struct ref_delta_entry *delta_a = a;
	const struct ref_delta_entry *delta_b = b;

	return hashcmp(delta_a->sha1, delta_b->sha1);
}