int committer_ident_sufficiently_given(void)
{
	return ident_is_sufficient(committer_ident_explicitly_given);
}