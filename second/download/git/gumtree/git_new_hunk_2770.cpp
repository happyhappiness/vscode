	if (is_empty_file(am_path(state, "patch"))) {
		printf_ln(_("Patch is empty. Was it split wrong?"));
		die_user_resolve(state);
	}

	strbuf_addstr(&msg, "\n\n");
	strbuf_addbuf(&msg, &mi.log_message);
	strbuf_stripspace(&msg, 0);

	if (state->signoff)
		am_signoff(&msg);

	assert(!state->author_name);
