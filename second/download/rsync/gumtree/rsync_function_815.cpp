static int path_failure(int f_out, const char *dir, BOOL was_chdir)
{
	if (was_chdir)
		rsyserr(FLOG, errno, "chdir %s failed\n", dir);
	else
		rprintf(FLOG, "normalize_path(%s) failed\n", dir);
	io_printf(f_out, "@ERROR: chdir failed\n");
	return -1;
}