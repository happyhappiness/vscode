		 * status.
		 */
		fn->cmdline = xstrdup(value);
		return 0;
	}

	if (!strcmp("recursive", key))
		return git_config_string(&fn->recursive, var, value);

	return 0;
}

static void initialize_ll_merge(void)
{
