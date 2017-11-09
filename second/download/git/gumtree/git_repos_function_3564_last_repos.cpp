static int has_rerere_resolution(const struct rerere_id *id)
{
	const int both = RR_HAS_POSTIMAGE|RR_HAS_PREIMAGE;
	int variant = id->variant;

	if (variant < 0)
		return 0;
	return ((id->collection->status[variant] & both) == both);
}