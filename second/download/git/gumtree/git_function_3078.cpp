static char *gitdiff_verify_name(const char *line, int isnull, char *orig_name, int side)
{
	if (!orig_name && !isnull)
		return find_name(line, NULL, p_value, TERM_TAB);

	if (orig_name) {
		int len = strlen(orig_name);
		char *another;
		if (isnull)
			die(_("git apply: bad git-diff - expected /dev/null, got %s on line %d"),
			    orig_name, linenr);
		another = find_name(line, NULL, p_value, TERM_TAB);
		if (!another || memcmp(another, orig_name, len + 1))
			die((side == DIFF_NEW_NAME) ?
			    _("git apply: bad git-diff - inconsistent new filename on line %d") :
			    _("git apply: bad git-diff - inconsistent old filename on line %d"), linenr);
		free(another);
		return orig_name;
	} else {
		/* expect "/dev/null" */
		if (memcmp("/dev/null", line, 9) || line[9] != '\n')
			die(_("git apply: bad git-diff - expected /dev/null on line %d"), linenr);
		return NULL;
	}
}