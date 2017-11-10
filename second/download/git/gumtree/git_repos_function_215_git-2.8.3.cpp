static struct combine_diff_path *find_paths_multitree(
	const unsigned char *sha1, const struct sha1_array *parents,
	struct diff_options *opt)
{
	int i, nparent = parents->nr;
	const unsigned char **parents_sha1;
	struct combine_diff_path paths_head;
	struct strbuf base;

	ALLOC_ARRAY(parents_sha1, nparent);
	for (i = 0; i < nparent; i++)
		parents_sha1[i] = parents->sha1[i];

	/* fake list head, so worker can assume it is non-NULL */
	paths_head.next = NULL;

	strbuf_init(&base, PATH_MAX);
	diff_tree_paths(&paths_head, sha1, parents_sha1, nparent, &base, opt);

	strbuf_release(&base);
	free(parents_sha1);
	return paths_head.next;
}