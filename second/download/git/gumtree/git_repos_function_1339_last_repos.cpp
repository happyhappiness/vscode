static int gitdiff_verify_name(struct apply_state *state,
			       const char *line,
			       int isnull,
			       char **name,
			       int side)
{
	if (!*name && !isnull) {
		*name = find_name(state, line, NULL, state->p_value, TERM_TAB);
		return 0;
	}

	if (*name) {
		char *another;
		if (isnull)
			return error(_("git apply: bad git-diff - expected /dev/null, got %s on line %d"),
				     *name, state->linenr);
		another = find_name(state, line, NULL, state->p_value, TERM_TAB);
		if (!another || strcmp(another, *name)) {
			free(another);
			return error((side == DIFF_NEW_NAME) ?
			    _("git apply: bad git-diff - inconsistent new filename on line %d") :
			    _("git apply: bad git-diff - inconsistent old filename on line %d"), state->linenr);
		}
		free(another);
	} else {
		if (!starts_with(line, "/dev/null\n"))
			return error(_("git apply: bad git-diff - expected /dev/null on line %d"), state->linenr);
	}

	return 0;
}