static int files_reflog_exists(struct ref_store *ref_store,
			       const char *refname)
{
	struct stat st;

	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "reflog_exists");

	return !lstat(git_path("logs/%s", refname), &st) &&
		S_ISREG(st.st_mode);
}