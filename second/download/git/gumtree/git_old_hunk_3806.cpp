	}
	if (args->atomic && !atomic_supported)
		die(_("the receiving end does not support --atomic push"));

	use_atomic = atomic_supported && args->atomic;

	if (status_report)
		strbuf_addstr(&cap_buf, " report-status");
	if (use_sideband)
		strbuf_addstr(&cap_buf, " side-band-64k");
	if (quiet_supported && (args->quiet || !args->progress))
		strbuf_addstr(&cap_buf, " quiet");
	if (use_atomic)
		strbuf_addstr(&cap_buf, " atomic");
	if (agent_supported)
		strbuf_addf(&cap_buf, " agent=%s", git_user_agent_sanitized());

	/*
	 * NEEDSWORK: why does delete-refs have to be so specific to
	 * send-pack machinery that set_ref_status_for_push() cannot
