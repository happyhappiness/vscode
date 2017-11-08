static int gitdiff_oldname(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	return gitdiff_verify_name(state, line,
				   patch->is_new, &patch->old_name,
				   DIFF_OLD_NAME);
}