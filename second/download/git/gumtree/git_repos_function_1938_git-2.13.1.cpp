static void diff_index_show_file(struct rev_info *revs,
				 const char *prefix,
				 const struct cache_entry *ce,
				 const unsigned char *sha1, int sha1_valid,
				 unsigned int mode,
				 unsigned dirty_submodule)
{
	diff_addremove(&revs->diffopt, prefix[0], mode,
		       sha1, sha1_valid, ce->name, dirty_submodule);
}