
	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", data->name);
	} else if (flags & TRANSPORT_PUSH_CERT) {
		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
			die("helper %s does not support dry-run", data->name);
	}

	if (flags & TRANSPORT_PUSH_FORCE) {
		if (set_helper_option(transport, "force", "true") != 0)
			warning("helper %s does not support 'force'", data->name);
	}
