int main(int argc, char **argv)
{
	char *dir;
	int i;
	int strict = 0;

	git_setup_gettext();

	packet_trace_identity("upload-pack");
	git_extract_argv0_path(argv[0]);
	check_replace_refs = 0;

	for (i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (arg[0] != '-')
			break;
		if (!strcmp(arg, "--advertise-refs")) {
			advertise_refs = 1;
			continue;
		}
		if (!strcmp(arg, "--stateless-rpc")) {
			stateless_rpc = 1;
			continue;
		}
		if (!strcmp(arg, "--strict")) {
			strict = 1;
			continue;
		}
		if (starts_with(arg, "--timeout=")) {
			timeout = atoi(arg+10);
			daemon_mode = 1;
			continue;
		}
		if (!strcmp(arg, "--")) {
			i++;
			break;
		}
	}

	if (i != argc-1)
		usage(upload_pack_usage);

	setup_path();

	dir = argv[i];

	if (!enter_repo(dir, strict))
		die("'%s' does not appear to be a git repository", dir);

	git_config(upload_pack_config, NULL);
	upload_pack();
	return 0;
}