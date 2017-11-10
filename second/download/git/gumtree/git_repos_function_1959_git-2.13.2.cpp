int run_diff_index(struct rev_info *revs, int cached)
{
	struct object_array_entry *ent;

	ent = revs->pending.objects;
	if (diff_cache(revs, ent->item->oid.hash, ent->name, cached))
		exit(128);

	diff_set_mnemonic_prefix(&revs->diffopt, "c/", cached ? "i/" : "w/");
	diffcore_fix_diff_index(&revs->diffopt);
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}