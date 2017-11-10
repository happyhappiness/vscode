int cmd_unpack_file(int argc, const char **argv, const char *prefix)
{
	unsigned char sha1[20];

	if (argc != 2 || !strcmp(argv[1], "-h"))
		usage("git unpack-file <sha1>");
	if (get_sha1(argv[1], sha1))
		die("Not a valid object name %s", argv[1]);

	git_config(git_default_config, NULL);

	puts(create_temp_file(sha1));
	return 0;
}