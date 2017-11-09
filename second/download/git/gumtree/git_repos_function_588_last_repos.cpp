static enum contains_result contains_test(struct commit *candidate,
					  const struct commit_list *want,
					  struct contains_cache *cache)
{
	enum contains_result *cached = contains_cache_at(cache, candidate);

	/* If we already have the answer cached, return that. */
	if (*cached)
		return *cached;

	/* or are we it? */
	if (in_commit_list(want, candidate)) {
		*cached = CONTAINS_YES;
		return CONTAINS_YES;
	}

	/* Otherwise, we don't know; prepare to recurse */
	parse_commit_or_die(candidate);
	return CONTAINS_UNKNOWN;
}