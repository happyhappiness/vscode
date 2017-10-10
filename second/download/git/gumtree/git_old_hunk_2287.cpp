			fprintf(stderr, "Server supports side-band\n");
		use_sideband = 1;
	}
	if (server_supports("allow-tip-sha1-in-want")) {
		if (args->verbose)
			fprintf(stderr, "Server supports allow-tip-sha1-in-want\n");
		allow_tip_sha1_in_want = 1;
	}
	if (!server_supports("thin-pack"))
		args->use_thin_pack = 0;
	if (!server_supports("no-progress"))
		args->no_progress = 0;
	if (!server_supports("include-tag"))
