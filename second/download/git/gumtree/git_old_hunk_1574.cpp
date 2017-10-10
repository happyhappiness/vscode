		ret = 1;

	free(gitdir);
	return ret;
}

int parse_submodule_update_strategy(const char *value,
		struct submodule_update_strategy *dst)
{
	free((void*)dst->command);
	dst->command = NULL;
	if (!strcmp(value, "none"))
