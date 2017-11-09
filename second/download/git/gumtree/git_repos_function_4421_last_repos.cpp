static void read_config(void)
{
	static int loaded;
	struct object_id oid;
	int flag;

	if (loaded)
		return;
	loaded = 1;

	current_branch = NULL;
	if (startup_info->have_repository) {
		const char *head_ref = resolve_ref_unsafe("HEAD", 0, oid.hash, &flag);
		if (head_ref && (flag & REF_ISSYMREF) &&
		    skip_prefix(head_ref, "refs/heads/", &head_ref)) {
			current_branch = make_branch(head_ref, 0);
		}
	}
	git_config(handle_config, NULL);
	alias_all_urls();
}