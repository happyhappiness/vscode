int read_mailmap(struct string_list *map, char **repo_abbrev)
{
	int err = 0;

	map->strdup_strings = 1;
	map->cmp = namemap_cmp;

	if (!git_mailmap_blob && is_bare_repository())
		git_mailmap_blob = "HEAD:.mailmap";

	err |= read_mailmap_file(map, ".mailmap", repo_abbrev);
	if (startup_info->have_repository)
		err |= read_mailmap_blob(map, git_mailmap_blob, repo_abbrev);
	err |= read_mailmap_file(map, git_mailmap_file, repo_abbrev);
	return err;
}