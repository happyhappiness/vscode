static void display_name(struct commit_name *n)
{
	if (n->prio == 2 && !n->tag) {
		n->tag = lookup_tag(n->sha1);
		if (!n->tag || parse_tag(n->tag))
			die(_("annotated tag %s not available"), n->path);
	}
	if (n->tag && !n->name_checked) {
		if (!n->tag->tag)
			die(_("annotated tag %s has no embedded name"), n->path);
		if (strcmp(n->tag->tag, all ? n->path + 5 : n->path))
			warning(_("tag '%s' is really '%s' here"), n->tag->tag, n->path);
		n->name_checked = 1;
	}

	if (n->tag)
		printf("%s", n->tag->tag);
	else
		printf("%s", n->path);
}