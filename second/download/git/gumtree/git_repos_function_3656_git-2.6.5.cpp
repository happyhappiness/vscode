static void read_config(void)
{
	static int loaded;
	unsigned char sha1[20];
	const char *head_ref;
	int flag;

	if (loaded)
		return;
	loaded = 1;

	current_branch = NULL;
	head_ref = resolve_ref_unsafe("HEAD", 0, sha1, &flag);
	if (head_ref && (flag & REF_ISSYMREF) &&
	    skip_prefix(head_ref, "refs/heads/", &head_ref)) {
		current_branch = make_branch(head_ref, 0);
	}
	git_config(handle_config, NULL);
	alias_all_urls();
}