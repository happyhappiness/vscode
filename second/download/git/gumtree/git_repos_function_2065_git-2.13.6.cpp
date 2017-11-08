void add_to_alternates_memory(const char *reference)
{
	/*
	 * Make sure alternates are initialized, or else our entry may be
	 * overwritten when they are.
	 */
	prepare_alt_odb();

	link_alt_odb_entries(reference, strlen(reference), '\n', NULL, 0);
}