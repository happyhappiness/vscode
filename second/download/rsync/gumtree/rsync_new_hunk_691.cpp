 void _exit_cleanup(int code, const char *file, int line)
{
	fprintf(stderr, "exit(%d): %s(%d)\n",
		code, file, line);
	exit(code);
}

 int check_exclude(UNUSED(struct exclude_struct **list), UNUSED(char *name),
		   UNUSED(int name_is_dir))
{
	/* This function doesn't really get called in this test context, so
	 * just return 0. */
	return 0;
}

 char *lp_name(UNUSED(int mod))
{
    return NULL;
}

 BOOL lp_use_chroot(UNUSED(int mod))
{
    return 0;
}

 char *lp_path(UNUSED(int mod))
{
    return NULL;
}

