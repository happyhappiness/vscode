	return 1;
}

int cmd_receive_pack(int argc, const char **argv, const char *prefix)
{
	int advertise_refs = 0;
	int i;
	struct command *commands;
	struct sha1_array shallow = SHA1_ARRAY_INIT;
	struct sha1_array ref = SHA1_ARRAY_INIT;
	struct shallow_info si;

	packet_trace_identity("receive-pack");

	argv++;
	for (i = 1; i < argc; i++) {
		const char *arg = *argv++;

		if (*arg == '-') {
			if (!strcmp(arg, "--quiet")) {
				quiet = 1;
				continue;
			}

			if (!strcmp(arg, "--advertise-refs")) {
				advertise_refs = 1;
				continue;
			}
			if (!strcmp(arg, "--stateless-rpc")) {
				stateless_rpc = 1;
				continue;
			}
			if (!strcmp(arg, "--reject-thin-pack-for-testing")) {
				fix_thin = 0;
				continue;
			}

			usage(receive_pack_usage);
		}
		if (service_dir)
			usage(receive_pack_usage);
		service_dir = arg;
	}
	if (!service_dir)
		usage(receive_pack_usage);

	setup_path();

	if (!enter_repo(service_dir, 0))
		die("'%s' does not appear to be a git repository", service_dir);

