struct ref_iterator *refs_ref_iterator_begin(
		struct ref_store *refs,
		const char *prefix, int trim, int flags)
{
	struct ref_iterator *iter;

	if (ref_paranoia < 0)
		ref_paranoia = git_env_bool("GIT_REF_PARANOIA", 0);
	if (ref_paranoia)
		flags |= DO_FOR_EACH_INCLUDE_BROKEN;

	iter = refs->be->iterator_begin(refs, prefix, flags);

	/*
	 * `iterator_begin()` already takes care of prefix, but we
	 * might need to do some trimming:
	 */
	if (trim)
		iter = prefix_ref_iterator_begin(iter, "", trim);

	return iter;
}