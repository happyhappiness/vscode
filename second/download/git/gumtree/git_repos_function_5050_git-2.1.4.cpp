static void index_commit_for_bitmap(struct commit *commit)
{
	if (indexed_commits_nr >= indexed_commits_alloc) {
		indexed_commits_alloc = (indexed_commits_alloc + 32) * 2;
		indexed_commits = xrealloc(indexed_commits,
			indexed_commits_alloc * sizeof(struct commit *));
	}

	indexed_commits[indexed_commits_nr++] = commit;
}