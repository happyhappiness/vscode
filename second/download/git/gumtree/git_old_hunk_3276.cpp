static char *gitdiff_verify_name(const char *line, int isnull, char *orig_name, int side)
{
	if (!orig_name && !isnull)
		return find_name(line, NULL, p_value, TERM_TAB);

	if (orig_name) {
		int len;
		const char *name;
		char *another;
		name = orig_name;
		len = strlen(name);
		if (isnull)
			die(_("git apply: bad git-diff - expected /dev/null, got %s on line %d"), name, linenr);
		another = find_name(line, NULL, p_value, TERM_TAB);
		if (!another || memcmp(another, name, len + 1))
			die((side == DIFF_NEW_NAME) ?
			    _("git apply: bad git-diff - inconsistent new filename on line %d") :
			    _("git apply: bad git-diff - inconsistent old filename on line %d"), linenr);
		free(another);
		return orig_name;
	}
	else {
		/* expect "/dev/null" */
		if (memcmp("/dev/null", line, 9) || line[9] != '\n')
			die(_("git apply: bad git-diff - expected /dev/null on line %d"), linenr);
		return NULL;
	}
}

static int gitdiff_oldname(const char *line, struct patch *patch)
{
	char *orig = patch->old_name;
	patch->old_name = gitdiff_verify_name(line, patch->is_new, patch->old_name,
					      DIFF_OLD_NAME);
	if (orig != patch->old_name)
		free(orig);
	return 0;
}

static int gitdiff_newname(const char *line, struct patch *patch)
{
	char *orig = patch->new_name;
	patch->new_name = gitdiff_verify_name(line, patch->is_delete, patch->new_name,
					      DIFF_NEW_NAME);
	if (orig != patch->new_name)
		free(orig);
	return 0;
}

static int gitdiff_oldmode(const char *line, struct patch *patch)
{
	patch->old_mode = strtoul(line, NULL, 8);
