static int check_everything_connected_real(sha1_iterate_fn fn,
					   int quiet,
					   void *cb_data,
					   struct transport *transport,
					   const char *shallow_file)
{
	struct child_process rev_list = CHILD_PROCESS_INIT;
	const char *argv[9];
	char commit[41];
	unsigned char sha1[20];
	int err = 0, ac = 0;
	struct packed_git *new_pack = NULL;
	size_t base_len;

	if (fn(cb_data, sha1))
		return err;

	if (transport && transport->smart_options &&
	    transport->smart_options->self_contained_and_connected &&
	    transport->pack_lockfile &&
	    strip_suffix(transport->pack_lockfile, ".keep", &base_len)) {
		struct strbuf idx_file = STRBUF_INIT;
		strbuf_add(&idx_file, transport->pack_lockfile, base_len);
		strbuf_addstr(&idx_file, ".idx");
		new_pack = add_packed_git(idx_file.buf, idx_file.len, 1);
		strbuf_release(&idx_file);
	}

	if (shallow_file) {
		argv[ac++] = "--shallow-file";
		argv[ac++] = shallow_file;
	}
	argv[ac++] = "rev-list";
	argv[ac++] = "--objects";
	argv[ac++] = "--stdin";
	argv[ac++] = "--not";
	argv[ac++] = "--all";
	if (quiet)
		argv[ac++] = "--quiet";
	argv[ac] = NULL;

	rev_list.argv = argv;
	rev_list.git_cmd = 1;
	rev_list.in = -1;
	rev_list.no_stdout = 1;
	rev_list.no_stderr = quiet;
	if (start_command(&rev_list))
		return error(_("Could not run 'git rev-list'"));

	sigchain_push(SIGPIPE, SIG_IGN);

	commit[40] = '\n';
	do {
		/*
		 * If index-pack already checked that:
		 * - there are no dangling pointers in the new pack
		 * - the pack is self contained
		 * Then if the updated ref is in the new pack, then we
		 * are sure the ref is good and not sending it to
		 * rev-list for verification.
		 */
		if (new_pack && find_pack_entry_one(sha1, new_pack))
			continue;

		memcpy(commit, sha1_to_hex(sha1), 40);
		if (write_in_full(rev_list.in, commit, 41) < 0) {
			if (errno != EPIPE && errno != EINVAL)
				error_errno(_("failed write to rev-list"));
			err = -1;
			break;
		}
	} while (!fn(cb_data, sha1));

	if (close(rev_list.in))
		err = error_errno(_("failed to close rev-list's stdin"));

	sigchain_pop(SIGPIPE);
	return finish_command(&rev_list) || err;
}