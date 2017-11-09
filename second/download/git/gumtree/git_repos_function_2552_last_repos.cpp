static int ll_diff_tree_oid(const struct object_id *old_oid,
			    const struct object_id *new_oid,
			    struct strbuf *base, struct diff_options *opt)
{
	struct combine_diff_path phead, *p;
	pathchange_fn_t pathchange_old = opt->pathchange;

	phead.next = NULL;
	opt->pathchange = emit_diff_first_parent_only;
	diff_tree_paths(&phead, new_oid, &old_oid, 1, base, opt);

	for (p = phead.next; p;) {
		struct combine_diff_path *pprev = p;
		p = p->next;
		free(pprev);
	}

	opt->pathchange = pathchange_old;
	return 0;
}