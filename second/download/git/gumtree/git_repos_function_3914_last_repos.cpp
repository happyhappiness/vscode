static struct commit_list *next_interesting_parent(struct git_graph *graph,
						   struct commit_list *orig)
{
	struct commit_list *list;

	/*
	 * If revs->first_parent_only is set, only the first
	 * parent is interesting.  None of the others are.
	 */
	if (graph->revs->first_parent_only)
		return NULL;

	/*
	 * Return the next interesting commit after orig
	 */
	for (list = orig->next; list; list = list->next) {
		if (graph_is_interesting(graph, list->item))
			return list;
	}

	return NULL;
}