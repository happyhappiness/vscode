int cmd_send_pack(int argc, const char **argv, const char *prefix)
{
	int i, nr_refspecs = 0;
	const char **refspecs = NULL;
	const char *remote_name = NULL;
	struct remote *remote = NULL;
	const char *dest = NULL;
	int fd[2];
	struct child_process *conn;
	struct sha1_array extra_have = SHA1_ARRAY_INIT;
	struct sha1_array shallow = SHA1_ARRAY_INIT;
	struct ref *remote_refs, *local_refs;
	int ret;
	int helper_status = 0;
	int send_all = 0;
	const char *receivepack = "git-receive-pack";
	int flags;
	unsigned int reject_reasons;
	int progress = -1;
	int from_stdin = 0;
	struct push_cas_option cas = {0};

	argv++;
	for (i = 1; i < argc; i++, argv++) {
		const char *arg = *argv;

		if (*arg == '-') {
			if (starts_with(arg, "--receive-pack=")) {
				receivepack = arg + 15;
				continue;
			}
			if (starts_with(arg, "--exec=")) {
				receivepack = arg + 7;
				continue;
			}
			if (starts_with(arg, "--remote=")) {
				remote_name = arg + 9;
				continue;
			}
			if (!strcmp(arg, "--all")) {
				send_all = 1;
				continue;
			}
			if (!strcmp(arg, "--dry-run")) {
				args.dry_run = 1;
				continue;
			}
			if (!strcmp(arg, "--mirror")) {
				args.send_mirror = 1;
				continue;
			}
			if (!strcmp(arg, "--force")) {
				args.force_update = 1;
				continue;
			}
			if (!strcmp(arg, "--quiet")) {
				args.quiet = 1;
				continue;
			}
			if (!strcmp(arg, "--verbose")) {
				args.verbose = 1;
				continue;
			}
			if (!strcmp(arg, "--signed")) {
				args.push_cert = 1;
				continue;
			}
			if (!strcmp(arg, "--progress")) {
				progress = 1;
				continue;
			}
			if (!strcmp(arg, "--no-progress")) {
				progress = 0;
				continue;
			}
			if (!strcmp(arg, "--thin")) {
				args.use_thin_pack = 1;
				continue;
			}
			if (!strcmp(arg, "--atomic")) {
				args.atomic = 1;
				continue;
			}
			if (!strcmp(arg, "--stateless-rpc")) {
				args.stateless_rpc = 1;
				continue;
			}
			if (!strcmp(arg, "--stdin")) {
				from_stdin = 1;
				continue;
			}
			if (!strcmp(arg, "--helper-status")) {
				helper_status = 1;
				continue;
			}
			if (!strcmp(arg, "--" CAS_OPT_NAME)) {
				if (parse_push_cas_option(&cas, NULL, 0) < 0)
					exit(1);
				continue;
			}
			if (!strcmp(arg, "--no-" CAS_OPT_NAME)) {
				if (parse_push_cas_option(&cas, NULL, 1) < 0)
					exit(1);
				continue;
			}
			if (starts_with(arg, "--" CAS_OPT_NAME "=")) {
				if (parse_push_cas_option(&cas,
							  strchr(arg, '=') + 1, 0) < 0)
					exit(1);
				continue;
			}
			usage(send_pack_usage);
		}
		if (!dest) {
			dest = arg;
			continue;
		}
		refspecs = (const char **) argv;
		nr_refspecs = argc - i;
		break;
	}
	if (!dest)
		usage(send_pack_usage);

	if (from_stdin) {
		struct argv_array all_refspecs = ARGV_ARRAY_INIT;

		for (i = 0; i < nr_refspecs; i++)
			argv_array_push(&all_refspecs, refspecs[i]);

		if (args.stateless_rpc) {
			const char *buf;
			while ((buf = packet_read_line(0, NULL)))
				argv_array_push(&all_refspecs, buf);
		} else {
			struct strbuf line = STRBUF_INIT;
			while (strbuf_getline(&line, stdin, '\n') != EOF)
				argv_array_push(&all_refspecs, line.buf);
			strbuf_release(&line);
		}

		refspecs = all_refspecs.argv;
		nr_refspecs = all_refspecs.argc;
	}

	/*
	 * --all and --mirror are incompatible; neither makes sense
	 * with any refspecs.
	 */
	if ((refspecs && (send_all || args.send_mirror)) ||
	    (send_all && args.send_mirror))
		usage(send_pack_usage);

	if (remote_name) {
		remote = remote_get(remote_name);
		if (!remote_has_url(remote, dest)) {
			die("Destination %s is not a uri for %s",
			    dest, remote_name);
		}
	}

	if (progress == -1)
		progress = !args.quiet && isatty(2);
	args.progress = progress;

	if (args.stateless_rpc) {
		conn = NULL;
		fd[0] = 0;
		fd[1] = 1;
	} else {
		conn = git_connect(fd, dest, receivepack,
			args.verbose ? CONNECT_VERBOSE : 0);
	}

	get_remote_heads(fd[0], NULL, 0, &remote_refs, REF_NORMAL,
			 &extra_have, &shallow);

	transport_verify_remote_names(nr_refspecs, refspecs);

	local_refs = get_local_heads();

	flags = MATCH_REFS_NONE;

	if (send_all)
		flags |= MATCH_REFS_ALL;
	if (args.send_mirror)
		flags |= MATCH_REFS_MIRROR;

	/* match them up */
	if (match_push_refs(local_refs, &remote_refs, nr_refspecs, refspecs, flags))
		return -1;

	if (!is_empty_cas(&cas))
		apply_push_cas(&cas, remote, remote_refs);

	set_ref_status_for_push(remote_refs, args.send_mirror,
		args.force_update);

	ret = send_pack(&args, fd, conn, remote_refs, &extra_have);

	if (helper_status)
		print_helper_status(remote_refs);

	close(fd[1]);
	close(fd[0]);

	ret |= finish_connect(conn);

	if (!helper_status)
		transport_print_push_status(dest, remote_refs, args.verbose, 0, &reject_reasons);

	if (!args.dry_run && remote) {
		struct ref *ref;
		for (ref = remote_refs; ref; ref = ref->next)
			transport_update_tracking_ref(remote, ref, args.verbose);
	}

	if (!ret && !transport_refs_pushed(remote_refs))
		fprintf(stderr, "Everything up-to-date\n");

	return ret;
}