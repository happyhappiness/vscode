static void add_options_to_argv(struct argv_array *argv)
{
	if (dry_run)
		argv_array_push(argv, "--dry-run");
	if (prune != -1)
		argv_array_push(argv, prune ? "--prune" : "--no-prune");
	if (update_head_ok)
		argv_array_push(argv, "--update-head-ok");
	if (force)
		argv_array_push(argv, "--force");
	if (keep)
		argv_array_push(argv, "--keep");
	if (recurse_submodules == RECURSE_SUBMODULES_ON)
		argv_array_push(argv, "--recurse-submodules");
	else if (recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND)
		argv_array_push(argv, "--recurse-submodules=on-demand");
	if (tags == TAGS_SET)
		argv_array_push(argv, "--tags");
	else if (tags == TAGS_UNSET)
		argv_array_push(argv, "--no-tags");
	if (verbosity >= 2)
		argv_array_push(argv, "-v");
	if (verbosity >= 1)
		argv_array_push(argv, "-v");
	else if (verbosity < 0)
		argv_array_push(argv, "-q");

}