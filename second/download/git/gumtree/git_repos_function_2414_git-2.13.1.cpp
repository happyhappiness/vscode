struct combine_diff_path *diff_tree_paths(
	struct combine_diff_path *p, const unsigned char *sha1,
	const unsigned char **parents_sha1, int nparent,
	struct strbuf *base, struct diff_options *opt)
{
	p = ll_diff_tree_paths(p, sha1, parents_sha1, nparent, base, opt);

	/*
	 * free pre-allocated last element, if any
	 * (see path_appendnew() for details about why)
	 */
	if (p->next) {
		free(p->next);
		p->next = NULL;
	}

	return p;
}