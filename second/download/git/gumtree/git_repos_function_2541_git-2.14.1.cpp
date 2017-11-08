struct combine_diff_path *diff_tree_paths(
	struct combine_diff_path *p, const struct object_id *oid,
	const struct object_id **parents_oid, int nparent,
	struct strbuf *base, struct diff_options *opt)
{
	p = ll_diff_tree_paths(p, oid, parents_oid, nparent, base, opt);

	/*
	 * free pre-allocated last element, if any
	 * (see path_appendnew() for details about why)
	 */
	if (p->next) {
		FREE_AND_NULL(p->next);
	}

	return p;
}