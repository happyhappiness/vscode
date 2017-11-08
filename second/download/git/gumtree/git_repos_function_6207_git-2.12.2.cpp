static int files_init_db(struct ref_store *ref_store, struct strbuf *err)
{
	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "init_db");

	/*
	 * Create .git/refs/{heads,tags}
	 */
	safe_create_dir(git_path("refs/heads"), 1);
	safe_create_dir(git_path("refs/tags"), 1);
	if (get_shared_repository()) {
		adjust_shared_perm(git_path("refs/heads"));
		adjust_shared_perm(git_path("refs/tags"));
	}
	return 0;
}