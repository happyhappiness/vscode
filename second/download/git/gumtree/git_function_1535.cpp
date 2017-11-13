int cmd_receive_pack(int argc, const char **argv, const char *prefix)
{
	int advertise_refs = 0;
	int stateless_rpc = 0;
	int i;
	const char *dir = NULL;
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
		if (dir)
			usage(receive_pack_usage);
		dir = arg;
	}
	if (!dir)
		usage(receive_pack_usage);

	setup_path();

	if (!enter_repo(dir, 0))
		die("'%s' does not appear to be a git repository", dir);

	git_config(receive_pack_config, NULL);

	if (0 <= transfer_unpack_limit)
		unpack_limit = transfer_unpack_limit;
	else if (0 <= receive_unpack_limit)
		unpack_limit = receive_unpack_limit;

	if (advertise_refs || !stateless_rpc) {
		write_head_info();
	}
	if (advertise_refs)
		return 0;

	if ((commands = read_head_info(&shallow)) != NULL) {
		const char *unpack_status = NULL;

		prepare_shallow_info(&si, &shallow);
		if (!si.nr_ours && !si.nr_theirs)
			shallow_update = 0;
		if (!delete_only(commands)) {
			unpack_status = unpack_with_sideband(&si);
			update_shallow_info(commands, &si, &ref);
		}
		execute_commands(commands, unpack_status, &si);
		if (pack_lockfile)
			unlink_or_warn(pack_lockfile);
		if (report_status)
			report(commands, unpack_status);
		run_receive_hook(commands, "post-receive", 1);
		run_update_post_hook(commands);
		if (auto_gc) {
			const char *argv_gc_auto[] = {
				"gc", "--auto", "--quiet", NULL,
			};
			int opt = RUN_GIT_CMD | RUN_COMMAND_STDOUT_TO_STDERR;
			run_command_v_opt(argv_gc_auto, opt);
		}
		if (auto_update_server_info)
			update_server_info(0);
		clear_shallow_info(&si);
	}
	if (use_sideband)
		packet_flush(1);
	sha1_array_clear(&shallow);
	sha1_array_clear(&ref);
	return 0;
}