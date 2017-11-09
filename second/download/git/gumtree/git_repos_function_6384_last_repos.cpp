static void acquire_packed_ref_cache(struct packed_ref_cache *packed_refs)
{
	packed_refs->referrers++;
}