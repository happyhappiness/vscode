void graph_update(struct git_graph *graph, struct commit *commit)
{
	struct commit_list *parent;

	/*
	 * Set the new commit
	 */
	graph->commit = commit;

	/*
	 * Count how many interesting parents this commit has
	 */
	graph->num_parents = 0;
	for (parent = first_interesting_parent(graph);
	     parent;
	     parent = next_interesting_parent(graph, parent))
	{
		graph->num_parents++;
	}

	/*
	 * Store the old commit_index in prev_commit_index.
	 * graph_update_columns() will update graph->commit_index for this
	 * commit.
	 */
	graph->prev_commit_index = graph->commit_index;

	/*
	 * Call graph_update_columns() to update
	 * columns, new_columns, and mapping.
	 */
	graph_update_columns(graph);

	graph->expansion_row = 0;

	/*
	 * Update graph->state.
	 * Note that we don't call graph_update_state() here, since
	 * we don't want to update graph->prev_state.  No line for
	 * graph->state was ever printed.
	 *
	 * If the previous commit didn't get to the GRAPH_PADDING state,
	 * it never finished its output.  Goto GRAPH_SKIP, to print out
	 * a line to indicate that portion of the graph is missing.
	 *
	 * If there are 3 or more parents, we may need to print extra rows
	 * before the commit, to expand the branch lines around it and make
	 * room for it.  We need to do this only if there is a branch row
	 * (or more) to the right of this commit.
	 *
	 * If there are less than 3 parents, we can immediately print the
	 * commit line.
	 */
	if (graph->state != GRAPH_PADDING)
		graph->state = GRAPH_SKIP;
	else if (graph->num_parents >= 3 &&
		 graph->commit_index < (graph->num_columns - 1))
		graph->state = GRAPH_PRE_COMMIT;
	else
		graph->state = GRAPH_COMMIT;
}