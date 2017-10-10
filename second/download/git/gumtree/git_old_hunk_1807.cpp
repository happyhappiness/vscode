		die_errno("unable to mkdir '%s'", dir);
	free(path_copy);
}

int main(int argc, const char **argv)
{
	socket_path = argv[1];

	if (!socket_path)
		die("usage: git-credential-cache--daemon <socket_path>");
	check_socket_directory(socket_path);

	atexit(cleanup_socket);
	sigchain_push_common(cleanup_socket_on_signal);

	serve_cache(socket_path);

	return 0;
}
