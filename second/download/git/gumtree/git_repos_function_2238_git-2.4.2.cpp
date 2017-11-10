static void cleanup_socket(void)
{
	if (socket_path)
		unlink(socket_path);
}