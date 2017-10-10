	for_each_string_list_item(cas_option, &cas_options)
		set_helper_option(transport, "cas", cas_option->string);

	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", data->name);
	}

	strbuf_addch(&buf, '\n');
	sendline(data, &buf);
	strbuf_release(&buf);

