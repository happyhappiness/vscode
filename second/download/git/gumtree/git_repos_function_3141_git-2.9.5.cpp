int parse_submodule_update_strategy(const char *value,
		struct submodule_update_strategy *dst)
{
	free((void*)dst->command);
	dst->command = NULL;
	if (!strcmp(value, "none"))
		dst->type = SM_UPDATE_NONE;
	else if (!strcmp(value, "checkout"))
		dst->type = SM_UPDATE_CHECKOUT;
	else if (!strcmp(value, "rebase"))
		dst->type = SM_UPDATE_REBASE;
	else if (!strcmp(value, "merge"))
		dst->type = SM_UPDATE_MERGE;
	else if (skip_prefix(value, "!", &value)) {
		dst->type = SM_UPDATE_COMMAND;
		dst->command = xstrdup(value);
	} else
		return -1;
	return 0;
}