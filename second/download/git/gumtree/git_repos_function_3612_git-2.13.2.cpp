static int submodule_has_commits(const char *path, struct oid_array *commits)
{
	int has_commit = 1;

	if (add_submodule_odb(path))
		return 0;

	oid_array_for_each_unique(commits, check_has_commit, &has_commit);
	return has_commit;
}