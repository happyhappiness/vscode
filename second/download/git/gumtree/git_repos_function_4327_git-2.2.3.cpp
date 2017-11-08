static int gitdiff_newfile(const char *line, struct patch *patch)
{
	patch->is_new = 1;
	free(patch->new_name);
	patch->new_name = null_strdup(patch->def_name);
	return gitdiff_newmode(line, patch);
}