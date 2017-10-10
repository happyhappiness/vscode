	if (is_empty_file(am_path(state, "patch"))) {
		printf_ln(_("Patch is empty. Was it split wrong?"));
		die_user_resolve(state);
	}

	strbuf_addstr(&msg, "\n\n");
	if (strbuf_read_file(&msg, am_path(state, "msg"), 0) < 0)
		die_errno(_("could not read '%s'"), am_path(state, "msg"));
	strbuf_stripspace(&msg, 0);

	if (state->signoff)
		am_signoff(&msg);

	assert(!state->author_name);
