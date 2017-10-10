		die_errno("unable to mkdir '%s'", dir);
	free(path_copy);
}

int main(int argc, const char **argv)
{
	static const char *usage[] = {
		"git-credential-cache--daemon [opts] <socket_path>",
		NULL
	};
	int debug = 0;
	const struct option options[] = {
		OPT_BOOL(0, "debug", &debug,
			 N_("print debugging messages to stderr")),
		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, options, usage, 0);
	socket_path = argv[0];

	if (!socket_path)
		usage_with_options(usage, options);
	check_socket_directory(socket_path);

	atexit(cleanup_socket);
	sigchain_push_common(cleanup_socket_on_signal);

	serve_cache(socket_path, debug);

	return 0;
}
