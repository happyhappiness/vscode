static void diff_index_show_file(struct rev_info *revs,
				 const char *prefix,
				 const struct cache_entry *ce,
				 const struct object_id *oid, int oid_valid,
				 unsigned int mode,
				 unsigned dirty_submodule)
{
	diff_addremove(&revs->diffopt, prefix[0], mode,
		       oid, oid_valid, ce->name, dirty_submodule);
}