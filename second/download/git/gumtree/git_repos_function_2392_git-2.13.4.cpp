static void set_untracked_ident(struct untracked_cache *uc)
{
	strbuf_reset(&uc->ident);
	strbuf_addstr(&uc->ident, get_ident_string());

	/*
	 * This strbuf used to contain a list of NUL separated
	 * strings, so save NUL too for backward compatibility.
	 */
	strbuf_addch(&uc->ident, 0);
}