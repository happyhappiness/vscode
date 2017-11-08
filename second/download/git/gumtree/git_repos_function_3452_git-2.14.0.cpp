struct ref_store *get_main_ref_store(void)
{
	if (main_ref_store)
		return main_ref_store;

	main_ref_store = ref_store_init(get_git_dir(), REF_STORE_ALL_CAPS);
	return main_ref_store;
}