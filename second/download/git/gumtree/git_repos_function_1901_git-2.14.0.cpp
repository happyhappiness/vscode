char *get_graft_file(void)
{
	if (!the_repository->graft_file)
		BUG("git environment hasn't been setup");
	return the_repository->graft_file;
}