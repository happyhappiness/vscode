
	prepare_packed_git();
	start_packfile();
	set_die_routine(die_nicely);
	set_checkpoint_signal();
	while (read_next_command() != EOF) {
		const char *v;
		if (!strcmp("blob", command_buf.buf))
			parse_new_blob();
		else if (skip_prefix(command_buf.buf, "ls ", &v))
			parse_ls(v, NULL);
		else if (skip_prefix(command_buf.buf, "commit ", &v))
			parse_new_commit(v);
		else if (skip_prefix(command_buf.buf, "tag ", &v))
			parse_new_tag(v);
		else if (skip_prefix(command_buf.buf, "reset ", &v))
			parse_reset_branch(v);
		else if (!strcmp("checkpoint", command_buf.buf))
			parse_checkpoint();
		else if (!strcmp("done", command_buf.buf))
			break;
		else if (starts_with(command_buf.buf, "progress "))
			parse_progress();
		else if (skip_prefix(command_buf.buf, "feature ", &v))
			parse_feature(v);
		else if (skip_prefix(command_buf.buf, "option git ", &v))
			parse_option(v);
		else if (starts_with(command_buf.buf, "option "))
			/* ignore non-git options*/;
		else
			die("Unsupported command: %s", command_buf.buf);

		if (checkpoint_requested)
