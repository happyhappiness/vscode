static int safe_to_abort(const struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;
	struct object_id abort_safety, head;

	if (file_exists(am_path(state, "dirtyindex")))
		return 0;

	if (read_state_file(&sb, state, "abort-safety", 1) > 0) {
		if (get_oid_hex(sb.buf, &abort_safety))
			die(_("could not parse %s"), am_path(state, "abort_safety"));
	} else
		oidclr(&abort_safety);

	if (get_oid("HEAD", &head))
		oidclr(&head);

	if (!oidcmp(&head, &abort_safety))
		return 1;

	error(_("You seem to have moved HEAD since the last 'am' failure.\n"
		"Not rewinding to ORIG_HEAD"));

	return 0;
}