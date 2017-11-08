static int upload_archive(void)
{
	static const char *argv[] = { "upload-archive", ".", NULL };
	return run_service_command(argv);
}