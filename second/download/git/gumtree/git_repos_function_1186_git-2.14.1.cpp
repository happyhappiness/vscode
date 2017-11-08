int repo_read_index(struct repository *repo)
{
	if (!repo->index)
		repo->index = xcalloc(1, sizeof(*repo->index));
	else
		discard_index(repo->index);

	return read_index_from(repo->index, repo->index_file);
}