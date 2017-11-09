const char *remote_for_branch(struct branch *branch, int *explicit)
{
	if (branch && branch->remote_name) {
		if (explicit)
			*explicit = 1;
		return branch->remote_name;
	}
	if (explicit)
		*explicit = 0;
	return "origin";
}