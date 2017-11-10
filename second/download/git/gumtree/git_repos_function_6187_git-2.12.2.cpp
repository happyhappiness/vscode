static int files_delete_reflog(struct ref_store *ref_store,
			       const char *refname)
{
	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "delete_reflog");

	return remove_path(git_path("logs/%s", refname));
}