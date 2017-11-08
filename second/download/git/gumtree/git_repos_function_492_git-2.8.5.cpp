static int filter_ref_kind(struct ref_filter *filter, const char *refname)
{
	unsigned int i;

	static struct {
		const char *prefix;
		unsigned int kind;
	} ref_kind[] = {
		{ "refs/heads/" , FILTER_REFS_BRANCHES },
		{ "refs/remotes/" , FILTER_REFS_REMOTES },
		{ "refs/tags/", FILTER_REFS_TAGS}
	};

	if (filter->kind == FILTER_REFS_BRANCHES ||
	    filter->kind == FILTER_REFS_REMOTES ||
	    filter->kind == FILTER_REFS_TAGS)
		return filter->kind;
	else if (!strcmp(refname, "HEAD"))
		return FILTER_REFS_DETACHED_HEAD;

	for (i = 0; i < ARRAY_SIZE(ref_kind); i++) {
		if (starts_with(refname, ref_kind[i].prefix))
			return ref_kind[i].kind;
	}

	return FILTER_REFS_OTHERS;
}