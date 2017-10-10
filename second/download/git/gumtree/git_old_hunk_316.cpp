 * 1. git-am previously failed because the index was dirty.
 * 2. HEAD has moved since git-am previously failed.
 */
static int safe_to_abort(const struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;
	unsigned char abort_safety[GIT_SHA1_RAWSZ], head[GIT_SHA1_RAWSZ];

	if (file_exists(am_path(state, "dirtyindex")))
		return 0;

	if (read_state_file(&sb, state, "abort-safety", 1) > 0) {
		if (get_sha1_hex(sb.buf, abort_safety))
			die(_("could not parse %s"), am_path(state, "abort_safety"));
	} else
		hashclr(abort_safety);

	if (get_sha1("HEAD", head))
		hashclr(head);

	if (!hashcmp(head, abort_safety))
		return 1;

	error(_("You seem to have moved HEAD since the last 'am' failure.\n"
		"Not rewinding to ORIG_HEAD"));

	return 0;
