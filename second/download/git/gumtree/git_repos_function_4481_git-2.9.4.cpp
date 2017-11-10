static void check_write(void)
{
	if (!given_config_source.file && !startup_info->have_repository)
		die("not in a git directory");

	if (given_config_source.use_stdin)
		die("writing to stdin is not supported");

	if (given_config_source.blob)
		die("writing config blobs is not supported");
}