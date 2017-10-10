		strbuf_replace(&cmd, TRAILER_ARG_STRING, arg);

	argv[0] = cmd.buf;
	cp.argv = argv;
	cp.env = local_repo_env;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.use_shell = 1;

	if (read_from_command(&cp, &buf)) {
		strbuf_release(&buf);
		result = xstrdup("");
	} else
		result = strbuf_detach(&buf, NULL);

	strbuf_release(&cmd);
	return result;
}

static void apply_item_command(struct trailer_item *in_tok, struct trailer_item *arg_tok)
