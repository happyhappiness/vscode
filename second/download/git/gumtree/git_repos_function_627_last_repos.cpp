static int include_condition_is_true(const struct config_options *opts,
				     const char *cond, size_t cond_len)
{

	if (skip_prefix_mem(cond, cond_len, "gitdir:", &cond, &cond_len))
		return include_by_gitdir(opts, cond, cond_len, 0);
	else if (skip_prefix_mem(cond, cond_len, "gitdir/i:", &cond, &cond_len))
		return include_by_gitdir(opts, cond, cond_len, 1);

	/* unknown conditionals are always false */
	return 0;
}