int cmd_receive_pack(int argc, const char **argv, const char *prefix)
{
	int advertise_refs = 0;
	struct command *commands;
	struct oid_array shallow = OID_ARRAY_INIT;
	struct oid_array ref = OID_ARRAY_INIT;
	struct shallow_info si;

	struct option options[] = {
		OPT__QUIET(&quiet, N_("quiet")),
		OPT_HIDDEN_BOOL(0, "stateless-rpc", &stateless_rpc, NULL),
		OPT_HIDDEN_BOOL(0, "advertise-refs", &advertise_refs, NULL),
		OPT_HIDDEN_BOOL(0, "reject-thin-pack-for-testing", &reject_thin, NULL),
		OPT_END()
	};

	packet_trace_identity("receive-pack");

	argc = parse_options(argc, argv, prefix, options, receive_pack_usage, 0);

	if (argc > 1)
		usage_msg_opt(_("Too many arguments."), receive_pack_usage, options);
	if (argc == 0)
		usage_msg_opt(_("You must specify a directory."), receive_pack_usage, options);

	service_dir = argv[0];

	setup_path();

	if (!enter_repo(service_dir, 0))
		die("'%s' does not appear to be a git repository", service_dir);

	git_config(receive_pack_config, NULL);
	if (cert_nonce_seed)
		push_cert_nonce = prepare_push_cert_nonce(service_dir, time(NULL));

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
		struct string_list push_options = STRING_LIST_INIT_DUP;

		if (use_push_options)
			read_push_options(&push_options);
		if (!check_cert_push_options(&push_options)) {
			struct command *cmd;
			for (cmd = commands; cmd; cmd = cmd->next)
				cmd->error_string = "inconsistent push options";
		}

		prepare_shallow_info(&si, &shallow);
		if (!si.nr_ours && !si.nr_theirs)
			shallow_update = 0;
		if (!delete_only(commands)) {
			unpack_status = unpack_with_sideband(&si);
			update_shallow_info(commands, &si, &ref);
		}
		use_keepalive = KEEPALIVE_ALWAYS;
		execute_commands(commands, unpack_status, &si,
				 &push_options);
		if (pack_lockfile)
			unlink_or_warn(pack_lockfile);
		if (report_status)
			report(commands, unpack_status);
		run_receive_hook(commands, "post-receive", 1,
				 &push_options);
		run_update_post_hook(commands);
		string_list_clear(&push_options, 0);
		if (auto_gc) {
			const char *argv_gc_auto[] = {
				"gc", "--auto", "--quiet", NULL,
			};
			struct child_process proc = CHILD_PROCESS_INIT;

			proc.no_stdin = 1;
			proc.stdout_to_stderr = 1;
			proc.err = use_sideband ? -1 : 0;
			proc.git_cmd = 1;
			proc.argv = argv_gc_auto;

			close_all_packs();
			if (!start_command(&proc)) {
				if (use_sideband)
					copy_to_sideband(proc.err, -1, NULL);
				finish_command(&proc);
			}
		}
		if (auto_update_server_info)
			update_server_info(0);
		clear_shallow_info(&si);
	}
	if (use_sideband)
		packet_flush(1);
	oid_array_clear(&shallow);
	oid_array_clear(&ref);
	free((void *)push_cert_nonce);
	return 0;
}