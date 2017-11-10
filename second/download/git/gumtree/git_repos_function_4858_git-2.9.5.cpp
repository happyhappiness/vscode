int cmd_reflog(int argc, const char **argv, const char *prefix)
{
	if (argc > 1 && !strcmp(argv[1], "-h"))
		usage(reflog_usage);

	/* With no command, we default to showing it. */
	if (argc < 2 || *argv[1] == '-')
		return cmd_log_reflog(argc, argv, prefix);

	if (!strcmp(argv[1], "show"))
		return cmd_log_reflog(argc - 1, argv + 1, prefix);

	if (!strcmp(argv[1], "expire"))
		return cmd_reflog_expire(argc - 1, argv + 1, prefix);

	if (!strcmp(argv[1], "delete"))
		return cmd_reflog_delete(argc - 1, argv + 1, prefix);

	if (!strcmp(argv[1], "exists"))
		return cmd_reflog_exists(argc - 1, argv + 1, prefix);

	return cmd_log_reflog(argc, argv, prefix);
}