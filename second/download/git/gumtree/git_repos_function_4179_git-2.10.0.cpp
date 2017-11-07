int xdl_fall_back_diff(xdfenv_t *diff_env, xpparam_t const *xpp,
		int line1, int count1, int line2, int count2)
{
	/*
	 * This probably does not work outside Git, since
	 * we have a very simple mmfile structure.
	 *
	 * Note: ideally, we would reuse the prepared environment, but
	 * the libxdiff interface does not (yet) allow for diffing only
	 * ranges of lines instead of the whole files.
	 */
	mmfile_t subfile1, subfile2;
	xdfenv_t env;

	subfile1.ptr = (char *)diff_env->xdf1.recs[line1 - 1]->ptr;
	subfile1.size = diff_env->xdf1.recs[line1 + count1 - 2]->ptr +
		diff_env->xdf1.recs[line1 + count1 - 2]->size - subfile1.ptr;
	subfile2.ptr = (char *)diff_env->xdf2.recs[line2 - 1]->ptr;
	subfile2.size = diff_env->xdf2.recs[line2 + count2 - 2]->ptr +
		diff_env->xdf2.recs[line2 + count2 - 2]->size - subfile2.ptr;
	if (xdl_do_diff(&subfile1, &subfile2, xpp, &env) < 0)
		return -1;

	memcpy(diff_env->xdf1.rchg + line1 - 1, env.xdf1.rchg, count1);
	memcpy(diff_env->xdf2.rchg + line2 - 1, env.xdf2.rchg, count2);

	xdl_free_env(&env);

	return 0;
}