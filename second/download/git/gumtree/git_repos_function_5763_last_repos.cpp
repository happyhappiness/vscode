static void check_not_current_branch(struct ref *ref_map)
{
	struct branch *current_branch = branch_get(NULL);

	if (is_bare_repository() || !current_branch)
		return;

	for (; ref_map; ref_map = ref_map->next)
		if (ref_map->peer_ref && !strcmp(current_branch->refname,
					ref_map->peer_ref->name))
			die(_("Refusing to fetch into current branch %s "
			    "of non-bare repository"), current_branch->refname);
}