static int gitdiff_newname(const char *line, struct patch *patch)
{
	char *orig = patch->new_name;
	patch->new_name = gitdiff_verify_name(line, patch->is_delete, patch->new_name,
					      DIFF_NEW_NAME);
	if (orig != patch->new_name)
		free(orig);
	return 0;
}