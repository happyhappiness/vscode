static int upload_pack(void)
{
	/* Timeout as string */
	char timeout_buf[64];
	const char *argv[] = { "upload-pack", "--strict", NULL, ".", NULL };

	argv[2] = timeout_buf;

	snprintf(timeout_buf, sizeof timeout_buf, "--timeout=%u", timeout);
	return run_service_command(argv);
}