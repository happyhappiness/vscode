static int check_header_line(struct apply_state *state, struct patch *patch)
{
	int extensions = (patch->is_delete == 1) + (patch->is_new == 1) +
			 (patch->is_rename == 1) + (patch->is_copy == 1);
	if (extensions > 1)
		return error(_("inconsistent header lines %d and %d"),
			     patch->extension_linenr, state->linenr);
	if (extensions && !patch->extension_linenr)
		patch->extension_linenr = state->linenr;
	return 0;
}