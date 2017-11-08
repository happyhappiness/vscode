void add_untracked_ident(struct untracked_cache *uc)
{
	if (ident_in_untracked(uc))
		return;
	strbuf_addstr(&uc->ident, get_ident_string());
	/* this strbuf contains a list of strings, save NUL too */
	strbuf_addch(&uc->ident, 0);
}