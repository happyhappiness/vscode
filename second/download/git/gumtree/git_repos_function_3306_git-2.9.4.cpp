static void graph_update_width(struct git_graph *graph,
			       int is_commit_in_existing_columns)
{
	/*
	 * Compute the width needed to display the graph for this commit.
	 * This is the maximum width needed for any row.  All other rows
	 * will be padded to this width.
	 *
	 * Compute the number of columns in the widest row:
	 * Count each existing column (graph->num_columns), and each new
	 * column added by this commit.
	 */
	int max_cols = graph->num_columns + graph->num_parents;

	/*
	 * Even if the current commit has no parents to be printed, it
	 * still takes up a column for itself.
	 */
	if (graph->num_parents < 1)
		max_cols++;

	/*
	 * We added a column for the current commit as part of
	 * graph->num_parents.  If the current commit was already in
	 * graph->columns, then we have double counted it.
	 */
	if (is_commit_in_existing_columns)
		max_cols--;

	/*
	 * Each column takes up 2 spaces
	 */
	graph->width = max_cols * 2;
}