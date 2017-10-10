	if (!data->refspecs)
		die("remote-helper doesn't support push; refspec needed");

	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", data->name);
	}

	if (flags & TRANSPORT_PUSH_FORCE) {
		if (set_helper_option(transport, "force", "true") != 0)
			warning("helper %s does not support 'force'", data->name);
	}
