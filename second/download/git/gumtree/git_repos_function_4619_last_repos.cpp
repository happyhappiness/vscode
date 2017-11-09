int author_ident_sufficiently_given(void)
{
	return ident_is_sufficient(author_ident_explicitly_given);
}