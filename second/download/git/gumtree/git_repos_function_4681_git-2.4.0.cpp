static int compare_delta_entry(const void *a, const void *b)
{
	const struct delta_entry *delta_a = a;
	const struct delta_entry *delta_b = b;

	/* group by type (ref vs ofs) and then by value (sha-1 or offset) */
	return compare_delta_bases(&delta_a->base, &delta_b->base,
				   objects[delta_a->obj_no].type,
				   objects[delta_b->obj_no].type);
}