static struct column *find_new_column_by_commit(struct git_graph *graph,
						struct commit *commit)
{
	int i;
	for (i = 0; i < graph->num_new_columns; i++) {
		if (graph->new_columns[i].commit == commit)
			return &graph->new_columns[i];
	}
	return NULL;
}