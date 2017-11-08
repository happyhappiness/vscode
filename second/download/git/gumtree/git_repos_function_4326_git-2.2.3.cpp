static int gitdiff_delete(const char *line, struct patch *patch)
{
	patch->is_delete = 1;
	free(patch->old_name);
	patch->old_name = null_strdup(patch->def_name);
	return gitdiff_oldmode(line, patch);
}