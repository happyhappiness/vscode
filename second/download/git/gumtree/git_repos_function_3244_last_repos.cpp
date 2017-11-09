static int verify_clean_submodule(const char *old_sha1,
				  const struct cache_entry *ce,
				  enum unpack_trees_error_types error_type,
				  struct unpack_trees_options *o)
{
	if (!submodule_from_ce(ce))
		return 0;

	return check_submodule_move_head(ce, old_sha1,
					 oid_to_hex(&ce->oid), o);
}