static void add_merge_info(const struct pretty_print_context *pp,
			   struct strbuf *sb, const struct commit *commit)
{
	struct commit_list *parent = commit->parents;

	if ((pp->fmt == CMIT_FMT_ONELINE) || (cmit_fmt_is_mail(pp->fmt)) ||
	    !parent || !parent->next)
		return;

	strbuf_addstr(sb, "Merge:");

	while (parent) {
		struct commit *p = parent->item;
		const char *hex = NULL;
		if (pp->abbrev)
			hex = find_unique_abbrev(p->object.oid.hash, pp->abbrev);
		if (!hex)
			hex = oid_to_hex(&p->object.oid);
		parent = parent->next;

		strbuf_addf(sb, " %s", hex);
	}
	strbuf_addch(sb, '\n');
}