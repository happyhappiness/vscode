static int ident_in_untracked(const struct untracked_cache *uc)
{
	/*
	 * Previous git versions may have saved many NUL separated
	 * strings in the "ident" field, but it is insane to manage
	 * many locations, so just take care of the first one.
	 */

	return !strcmp(uc->ident.buf, get_ident_string());
}