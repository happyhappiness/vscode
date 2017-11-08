static struct combine_diff_path *find_paths_multitree(
	const struct object_id *oid, const struct oid_array *parents,
	struct diff_options *opt)
{
	int i, nparent = parents->nr;
	const struct object_id **parents_oid;
	struct combine_diff_path paths_head;
	struct strbuf base;

	ALLOC_ARRAY(parents_oid, nparent);
	for (i = 0; i < nparent; i++)
		parents_oid[i] = &parents->oid[i];

	/* fake list head, so worker can assume it is non-NULL */
	paths_head.next = NULL;

	strbuf_init(&base, PATH_MAX);
	diff_tree_paths(&paths_head, oid, parents_oid, nparent, &base, opt);

	strbuf_release(&base);
	free(parents_oid);
	return paths_head.next;
}