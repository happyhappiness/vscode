const char *pushremote_for_branch(struct branch *branch, int *explicit)
{
	if (branch && branch->pushremote_name) {
		if (explicit)
			*explicit = 1;
		return branch->pushremote_name;
	}
	if (pushremote_name) {
		if (explicit)
			*explicit = 1;
		return pushremote_name;
	}
	return remote_for_branch(branch, explicit);
}