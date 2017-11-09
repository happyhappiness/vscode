static void prepare_replace_object(void)
{
	static int replace_object_prepared;

	if (replace_object_prepared)
		return;

	for_each_replace_ref(register_replace_ref, NULL);
	replace_object_prepared = 1;
	if (!replace_object_nr)
		check_replace_refs = 0;
}