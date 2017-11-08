int do_mknod(char *pathname, mode_t mode, dev_t dev)
{
	if (dry_run) return 0;
	return mknod(pathname, mode, dev);
}