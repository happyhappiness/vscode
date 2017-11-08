void advertise_shallow_grafts(int fd)
{
	if (!is_repository_shallow())
		return;
	for_each_commit_graft(advertise_shallow_grafts_cb, &fd);
}