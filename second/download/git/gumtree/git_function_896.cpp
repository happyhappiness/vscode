void assert_main_repository(struct ref_store *refs, const char *caller)
{
	if (*refs->submodule)
		die("BUG: %s called for a submodule", caller);
}