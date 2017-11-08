int do_mknod(char *pathname, mode_t mode, dev_t dev)
{
	if (dry_run) return 0;
	RETURN_ERROR_IF_RO_OR_LO;
	return mknod(pathname, mode, dev);
}