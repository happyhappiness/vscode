	struct string_list revlist_args = STRING_LIST_INIT_DUP;
	struct strbuf buf = STRBUF_INIT;

	if (!data->refspecs)
		die("remote-helper doesn't support push; refspec needed");

	set_common_push_options(transport, data->name, flags);
	if (flags & TRANSPORT_PUSH_FORCE) {
		if (set_helper_option(transport, "force", "true") != 0)
			warning("helper %s does not support 'force'", data->name);
	}

	helper = get_helper(transport);
