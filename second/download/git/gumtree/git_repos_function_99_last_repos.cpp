static void add_merge_info(const struct pretty_print_context *pp,
			   struct strbuf *sb, const struct commit *commit)
{
	struct commit_list *parent = commit->parents;

	if ((pp->fmt == CMIT_FMT_ONELINE) || (cmit_fmt_is_mail(pp->fmt)) ||
	    !parent || !parent->next)
		return;

	strbuf_addstr(sb, "Merge:");

	while (parent) {
		struct object_id *oidp = &parent->item->object.oid;
		strbuf_addch(sb, ' ');
		if (pp->abbrev)
			strbuf_add_unique_abbrev(sb, oidp->hash, pp->abbrev);
		else
			strbuf_addstr(sb, oid_to_hex(oidp));
		parent = parent->next;
	}
	strbuf_addch(sb, '\n');
}