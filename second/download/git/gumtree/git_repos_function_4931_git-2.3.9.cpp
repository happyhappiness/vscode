static void credit_people(struct strbuf *out,
			  struct string_list *them,
			  int kind)
{
	const char *label;
	const char *me;

	if (kind == 'a') {
		label = "By";
		me = git_author_info(IDENT_NO_DATE);
	} else {
		label = "Via";
		me = git_committer_info(IDENT_NO_DATE);
	}

	if (!them->nr ||
	    (them->nr == 1 &&
	     me &&
	     skip_prefix(me, them->items->string, &me) &&
	     starts_with(me, " <")))
		return;
	strbuf_addf(out, "\n%c %s ", comment_line_char, label);
	add_people_count(out, them);
}