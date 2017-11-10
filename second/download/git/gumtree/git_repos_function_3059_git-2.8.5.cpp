static int receive_pack(void)
{
	static const char *argv[] = { "receive-pack", ".", NULL };
	return run_service_command(argv);
}