			       struct transport *transport,
			       int check_connectivity)
{
	const struct ref *rm = mapped_refs;

	if (check_connectivity) {
		struct check_connected_options opt = CHECK_CONNECTED_INIT;

		opt.transport = transport;
		opt.progress = transport->progress;

		if (check_connected(iterate_ref_map, &rm, &opt))
			die(_("remote did not send all necessary objects"));
	}

	if (refs) {
		write_remote_refs(mapped_refs);
		if (option_single_branch)
			write_followtags(refs, msg);
