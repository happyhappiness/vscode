void prepare_alt_odb(void)
{
	const char *alt;

	if (alt_odb_tail)
		return;

	alt = getenv(ALTERNATE_DB_ENVIRONMENT);
	if (!alt) alt = "";

	alt_odb_tail = &alt_odb_list;
	link_alt_odb_entries(alt, strlen(alt), PATH_SEP, NULL, 0);

	read_info_alternates(get_object_directory(), 0);
}