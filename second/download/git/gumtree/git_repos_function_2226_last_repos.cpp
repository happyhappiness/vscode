void prepare_packed_git(void)
{
	struct alternate_object_database *alt;

	if (prepare_packed_git_run_once)
		return;
	prepare_packed_git_one(get_object_directory(), 1);
	prepare_alt_odb();
	for (alt = alt_odb_list; alt; alt = alt->next)
		prepare_packed_git_one(alt->path, 0);
	rearrange_packed_git();
	prepare_packed_git_mru();
	prepare_packed_git_run_once = 1;
}