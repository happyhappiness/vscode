		fn->name = xmemdupz(name, namelen);
		fn->fn = ll_ext_merge;
		*ll_user_merge_tail = fn;
		ll_user_merge_tail = &(fn->next);
	}

	if (!strcmp("name", key))
		return git_config_string(&fn->description, var, value);

	if (!strcmp("driver", key)) {
		if (!value)
			return error("%s: lacks value", var);
		/*
		 * merge.<name>.driver specifies the command line:
