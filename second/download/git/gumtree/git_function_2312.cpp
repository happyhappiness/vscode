static int append_ref(const char *refname, const struct object_id *oid, int flags, void *cb_data)
{
	struct append_ref_cb *cb = (struct append_ref_cb *)(cb_data);
	struct ref_list *ref_list = cb->ref_list;
	struct ref_item *newitem;
	struct commit *commit;
	int kind, i;
	const char *prefix, *orig_refname = refname;

	static struct {
		int kind;
		const char *prefix;
	} ref_kind[] = {
		{ REF_LOCAL_BRANCH, "refs/heads/" },
		{ REF_REMOTE_BRANCH, "refs/remotes/" },
	};

	/* Detect kind */
	for (i = 0; i < ARRAY_SIZE(ref_kind); i++) {
		prefix = ref_kind[i].prefix;
		if (skip_prefix(refname, prefix, &refname)) {
			kind = ref_kind[i].kind;
			break;
		}
	}
	if (ARRAY_SIZE(ref_kind) <= i)
		return 0;

	/* Don't add types the caller doesn't want */
	if ((kind & ref_list->kinds) == 0)
		return 0;

	if (!match_patterns(cb->pattern, refname))
		return 0;

	commit = NULL;
	if (ref_list->verbose || ref_list->with_commit || merge_filter != NO_FILTER) {
		commit = lookup_commit_reference_gently(oid->hash, 1);
		if (!commit) {
			cb->ret = error(_("branch '%s' does not point at a commit"), refname);
			return 0;
		}

		/* Filter with with_commit if specified */
		if (!is_descendant_of(commit, ref_list->with_commit))
			return 0;

		if (merge_filter != NO_FILTER)
			add_pending_object(&ref_list->revs,
					   (struct object *)commit, refname);
	}

	ALLOC_GROW(ref_list->list, ref_list->index + 1, ref_list->alloc);

	/* Record the new item */
	newitem = &(ref_list->list[ref_list->index++]);
	newitem->name = xstrdup(refname);
	newitem->kind = kind;
	newitem->commit = commit;
	newitem->width = utf8_strwidth(refname);
	newitem->dest = resolve_symref(orig_refname, prefix);
	newitem->ignore = 0;
	/* adjust for "remotes/" */
	if (newitem->kind == REF_REMOTE_BRANCH &&
	    ref_list->kinds != REF_REMOTE_BRANCH)
		newitem->width += 8;
	if (newitem->width > ref_list->maxwidth)
		ref_list->maxwidth = newitem->width;

	return 0;
}