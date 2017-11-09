int xdl_do_patience_diff(mmfile_t *file1, mmfile_t *file2,
		xpparam_t const *xpp, xdfenv_t *env)
{
	if (xdl_prepare_env(file1, file2, xpp, env) < 0)
		return -1;

	/* environment is cleaned up in xdl_diff() */
	return patience_diff(file1, file2, xpp, env,
			1, env->xdf1.nrec, 1, env->xdf2.nrec);
}