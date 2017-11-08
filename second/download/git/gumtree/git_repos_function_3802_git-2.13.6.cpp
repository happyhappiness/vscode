static int graph_draw_octopus_merge(struct git_graph *graph,
				    struct strbuf *sb)
{
	/*
	 * Here dashless_commits represents the number of parents
	 * which don't need to have dashes (because their edges fit
	 * neatly under the commit).
	 */
	const int dashless_commits = 2;
	int col_num, i;
	int num_dashes =
		((graph->num_parents - dashless_commits) * 2) - 1;
	for (i = 0; i < num_dashes; i++) {
		col_num = (i / 2) + dashless_commits + graph->commit_index;
		strbuf_write_column(sb, &graph->new_columns[col_num], '-');
	}
	col_num = (i / 2) + dashless_commits + graph->commit_index;
	strbuf_write_column(sb, &graph->new_columns[col_num], '.');
	return num_dashes + 1;
}