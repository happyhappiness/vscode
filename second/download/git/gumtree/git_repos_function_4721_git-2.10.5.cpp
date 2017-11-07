static int gitdiff_newfile(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	patch->is_new = 1;
	free(patch->new_name);
	patch->new_name = xstrdup_or_null(patch->def_name);
	return gitdiff_newmode(state, line, patch);
}