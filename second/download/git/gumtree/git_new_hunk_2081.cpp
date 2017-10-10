	for ( ; p; p = p->next) {
		printf(" %s", find_unique_abbrev(p->item->object.sha1, abbrev));
	}
}

/*
 * Do we have HEAD in the output, and also the branch it points at?
 * If so, find that decoration entry for that current branch.
 */
static const struct name_decoration *current_pointed_by_HEAD(const struct name_decoration *decoration)
{
	const struct name_decoration *list, *head = NULL;
	const char *branch_name = NULL;
	unsigned char unused[20];
	int rru_flags;

	/* First find HEAD */
	for (list = decoration; list; list = list->next)
		if (list->type == DECORATION_REF_HEAD) {
			head = list;
			break;
		}
	if (!head)
		return NULL;

	/* Now resolve and find the matching current branch */
	branch_name = resolve_ref_unsafe("HEAD", 0, unused, &rru_flags);
	if (!(rru_flags & REF_ISSYMREF))
		return NULL;
	if (!skip_prefix(branch_name, "refs/heads/", &branch_name))
		return NULL;

	/* OK, do we have that ref in the list? */
	for (list = decoration; list; list = list->next)
		if ((list->type == DECORATION_REF_LOCAL) &&
		    !strcmp(branch_name, list->name)) {
			return list;
		}

	return NULL;
}

/*
 * The caller makes sure there is no funny color before calling.
 * format_decorations_extended makes sure the same after return.
 */
void format_decorations_extended(struct strbuf *sb,
			const struct commit *commit,
			int use_color,
			const char *prefix,
			const char *separator,
			const char *suffix)
{
	const struct name_decoration *decoration;
	const struct name_decoration *current_and_HEAD;
	const char *color_commit =
		diff_get_color(use_color, DIFF_COMMIT);
	const char *color_reset =
		decorate_get_color(use_color, DECORATION_NONE);

	decoration = get_name_decoration(&commit->object);
	if (!decoration)
		return;

	current_and_HEAD = current_pointed_by_HEAD(decoration);
	while (decoration) {
		/*
		 * When both current and HEAD are there, only
		 * show HEAD->current where HEAD would have
		 * appeared, skipping the entry for current.
		 */
		if (decoration != current_and_HEAD) {
			strbuf_addstr(sb, color_commit);
			strbuf_addstr(sb, prefix);
			strbuf_addstr(sb, color_reset);
			strbuf_addstr(sb, decorate_get_color(use_color, decoration->type));
			if (decoration->type == DECORATION_REF_TAG)
				strbuf_addstr(sb, "tag: ");

			strbuf_addstr(sb, decoration->name);

			if (current_and_HEAD &&
			    decoration->type == DECORATION_REF_HEAD) {
				strbuf_addstr(sb, color_reset);
				strbuf_addstr(sb, color_commit);
				strbuf_addstr(sb, " -> ");
				strbuf_addstr(sb, color_reset);
				strbuf_addstr(sb, decorate_get_color(use_color, current_and_HEAD->type));
				strbuf_addstr(sb, current_and_HEAD->name);
			}
			strbuf_addstr(sb, color_reset);

			prefix = separator;
		}
		decoration = decoration->next;
	}
	strbuf_addstr(sb, color_commit);
	strbuf_addstr(sb, suffix);
	strbuf_addstr(sb, color_reset);
}
