int mkdir_defmode(char *fname)
{
	int ret;

	umask(orig_umask);
	ret = do_mkdir(fname, ACCESSPERMS);
	umask(0);

	return ret;
}