static void graph_insert_into_new_columns(struct git_graph *graph,
					  struct commit *commit,
					  int *mapping_index)
{
	int i;

	/*
	 * If the commit is already in the new_columns list, we don't need to
	 * add it.  Just update the mapping correctly.
	 */
	for (i = 0; i < graph->num_new_columns; i++) {
		if (graph->new_columns[i].commit == commit) {
			graph->mapping[*mapping_index] = i;
			*mapping_index += 2;
			return;
		}
	}

	/*
	 * This commit isn't already in new_columns.  Add it.
	 */
	graph->new_columns[graph->num_new_columns].commit = commit;
	graph->new_columns[graph->num_new_columns].color = graph_find_commit_color(graph, commit);
	graph->mapping[*mapping_index] = graph->num_new_columns;
	*mapping_index += 2;
	graph->num_new_columns++;
}