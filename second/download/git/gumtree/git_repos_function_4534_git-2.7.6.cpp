static int try_parent_shorthands(const char *arg)
{
	char *dotdot;
	unsigned char sha1[20];
	struct commit *commit;
	struct commit_list *parents;
	int parents_only;

	if ((dotdot = strstr(arg, "^!")))
		parents_only = 0;
	else if ((dotdot = strstr(arg, "^@")))
		parents_only = 1;

	if (!dotdot || dotdot[2])
		return 0;

	*dotdot = 0;
	if (get_sha1_committish(arg, sha1)) {
		*dotdot = '^';
		return 0;
	}

	if (!parents_only)
		show_rev(NORMAL, sha1, arg);
	commit = lookup_commit_reference(sha1);
	for (parents = commit->parents; parents; parents = parents->next)
		show_rev(parents_only ? NORMAL : REVERSED,
				parents->item->object.oid.hash, arg);

	*dotdot = '^';
	return 1;
}