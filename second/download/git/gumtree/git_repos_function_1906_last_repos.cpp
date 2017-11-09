char *get_object_directory(void)
{
	if (!the_repository->objectdir)
		BUG("git environment hasn't been setup");
	return the_repository->objectdir;
}