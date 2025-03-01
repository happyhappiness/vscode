int cmd_bundle(int argc, const char **argv, const char *prefix)
{
	struct bundle_header header;
	const char *cmd, *bundle_file;
	int bundle_fd = -1;
	char buffer[PATH_MAX];

	if (argc < 3)
		usage(builtin_bundle_usage);

	cmd = argv[1];
	bundle_file = argv[2];
	argc -= 2;
	argv += 2;

	if (prefix && bundle_file[0] != '/') {
		snprintf(buffer, sizeof(buffer), "%s/%s", prefix, bundle_file);
		bundle_file = buffer;
	}

	memset(&header, 0, sizeof(header));
	if (strcmp(cmd, "create") && (bundle_fd =
				read_bundle_header(bundle_file, &header)) < 0)
		return 1;

	if (!strcmp(cmd, "verify")) {
		close(bundle_fd);
		if (verify_bundle(&header, 1))
			return 1;
		fprintf(stderr, _("%s is okay\n"), bundle_file);
		return 0;
	}
	if (!strcmp(cmd, "list-heads")) {
		close(bundle_fd);
		return !!list_bundle_refs(&header, argc, argv);
	}
	if (!strcmp(cmd, "create")) {
		if (!startup_info->have_repository)
			die(_("Need a repository to create a bundle."));
		return !!create_bundle(&header, bundle_file, argc, argv);
	} else if (!strcmp(cmd, "unbundle")) {
		if (!startup_info->have_repository)
			die(_("Need a repository to unbundle."));
		return !!unbundle(&header, bundle_fd, 0) ||
			list_bundle_refs(&header, argc, argv);
	} else
		usage(builtin_bundle_usage);
}