static int gitdiff_oldname(const char *line, struct patch *patch)
{
	char *orig = patch->old_name;
	patch->old_name = gitdiff_verify_name(line, patch->is_new, patch->old_name,
					      DIFF_OLD_NAME);
	if (orig != patch->old_name)
		free(orig);
	return 0;
}