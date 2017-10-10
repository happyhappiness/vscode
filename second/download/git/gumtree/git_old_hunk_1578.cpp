			 const char *new,
			 unsigned flags)
{
	int ret = 0;
	struct child_process cp = CHILD_PROCESS_INIT;
	const struct submodule *sub;

	sub = submodule_from_path(null_sha1, path);

	if (!sub)
		die("BUG: could not get submodule information for '%s'", path);

