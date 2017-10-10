	if (info->header_prefix)
		fputs(info->header_prefix, stdout);

	if (!revs->graph)
		fputs(get_revision_mark(revs, commit), stdout);
	if (revs->abbrev_commit && revs->abbrev)
		fputs(find_unique_abbrev(commit->object.oid.hash, revs->abbrev),
		      stdout);
	else
		fputs(oid_to_hex(&commit->object.oid), stdout);
	if (revs->print_parents) {
		struct commit_list *parents = commit->parents;
		while (parents) {
			printf(" %s", oid_to_hex(&parents->item->object.oid));
			parents = parents->next;
		}
	}
	if (revs->children.name) {
		struct commit_list *children;

		children = lookup_decoration(&revs->children, &commit->object);
		while (children) {
			printf(" %s", oid_to_hex(&children->item->object.oid));
			children = children->next;
		}
	}
	show_decorations(revs, commit);
	if (revs->commit_format == CMIT_FMT_ONELINE)
		putchar(' ');
