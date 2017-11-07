int cmd_patch_id(int argc, const char **argv, const char *prefix)
{
	if (argc != 1)
		usage(patch_id_usage);

	generate_id_list();
	return 0;
}