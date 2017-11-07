static void read_config(void)
{
	unsigned char sha1[20];
	const char *head_ref;
	int flag;
	if (default_remote_name) /* did this already */
		return;
	default_remote_name = "origin";
	current_branch = NULL;
	head_ref = resolve_ref_unsafe("HEAD", sha1, 0, &flag);
	if (head_ref && (flag & REF_ISSYMREF) &&
	    starts_with(head_ref, "refs/heads/")) {
		current_branch =
			make_branch(head_ref + strlen("refs/heads/"), 0);
	}
	git_config(handle_config, NULL);
	if (branch_pushremote_name) {
		free((char *)pushremote_name);
		pushremote_name = branch_pushremote_name;
	}
	alias_all_urls();
}