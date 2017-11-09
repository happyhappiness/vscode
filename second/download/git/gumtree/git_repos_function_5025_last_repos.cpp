static const char *get_tracking_branch(const char *remote, const char *refspec)
{
	struct refspec *spec;
	const char *spec_src;
	const char *merge_branch;

	spec = parse_fetch_refspec(1, &refspec);
	spec_src = spec->src;
	if (!*spec_src || !strcmp(spec_src, "HEAD"))
		spec_src = "HEAD";
	else if (skip_prefix(spec_src, "heads/", &spec_src))
		;
	else if (skip_prefix(spec_src, "refs/heads/", &spec_src))
		;
	else if (starts_with(spec_src, "refs/") ||
		starts_with(spec_src, "tags/") ||
		starts_with(spec_src, "remotes/"))
		spec_src = "";

	if (*spec_src) {
		if (!strcmp(remote, "."))
			merge_branch = mkpath("refs/heads/%s", spec_src);
		else
			merge_branch = mkpath("refs/remotes/%s/%s", remote, spec_src);
	} else
		merge_branch = NULL;

	free_refspec(1, spec);
	return merge_branch;
}