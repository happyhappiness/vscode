static int do_unresolve(int ac, const char **av,
			const char *prefix, int prefix_length)
{
	int i;
	int err = 0;

	/* Read HEAD and MERGE_HEAD; if MERGE_HEAD does not exist, we
	 * are not doing a merge, so exit with success status.
	 */
	read_head_pointers();

	for (i = 1; i < ac; i++) {
		const char *arg = av[i];
		char *p = prefix_path(prefix, prefix_length, arg);
		err |= unresolve_one(p);
		free(p);
	}
	return err;
}