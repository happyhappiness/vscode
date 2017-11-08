static struct commit_list *first_interesting_parent(struct git_graph *graph)
{
	struct commit_list *parents = graph->commit->parents;

	/*
	 * If this commit has no parents, ignore it
	 */
	if (!parents)
		return NULL;

	/*
	 * If the first parent is interesting, return it
	 */
	if (graph_is_interesting(graph, parents->item))
		return parents;

	/*
	 * Otherwise, call next_interesting_parent() to get
	 * the next interesting parent
	 */
	return next_interesting_parent(graph, parents);
}