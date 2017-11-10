static int gitdiff_newname(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	return gitdiff_verify_name(state, line,
				   patch->is_delete, &patch->new_name,
				   DIFF_NEW_NAME);
}