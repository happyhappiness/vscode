struct ref_store *get_main_ref_store(void)
{
	if (main_ref_store)
		return main_ref_store;

	main_ref_store = ref_store_init(get_git_dir(),
					(REF_STORE_READ |
					 REF_STORE_WRITE |
					 REF_STORE_ODB |
					 REF_STORE_MAIN));
	return main_ref_store;
}