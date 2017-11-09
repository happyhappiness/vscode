static struct combine_diff_path *ll_diff_tree_paths(
	struct combine_diff_path *p, const struct object_id *oid,
	const struct object_id **parents_oid, int nparent,
	struct strbuf *base, struct diff_options *opt)
{
	struct tree_desc t, *tp;
	void *ttree, **tptree;
	int i;

	FAST_ARRAY_ALLOC(tp, nparent);
	FAST_ARRAY_ALLOC(tptree, nparent);

	/*
	 * load parents first, as they are probably already cached.
	 *
	 * ( log_tree_diff() parses commit->parent before calling here via
	 *   diff_tree_oid(parent, commit) )
	 */
	for (i = 0; i < nparent; ++i)
		tptree[i] = fill_tree_descriptor(&tp[i], parents_oid[i]->hash);
	ttree = fill_tree_descriptor(&t, oid->hash);

	/* Enable recursion indefinitely */
	opt->pathspec.recursive = DIFF_OPT_TST(opt, RECURSIVE);

	for (;;) {
		int imin, cmp;

		if (diff_can_quit_early(opt))
			break;

		if (opt->pathspec.nr) {
			skip_uninteresting(&t, base, opt);
			for (i = 0; i < nparent; i++)
				skip_uninteresting(&tp[i], base, opt);
		}

		/* comparing is finished when all trees are done */
		if (!t.size) {
			int done = 1;
			for (i = 0; i < nparent; ++i)
				if (tp[i].size) {
					done = 0;
					break;
				}
			if (done)
				break;
		}

		/*
		 * lookup imin = argmin(p1...pn),
		 * mark entries whether they =p[imin] along the way
		 */
		imin = 0;
		tp[0].entry.mode &= ~S_IFXMIN_NEQ;

		for (i = 1; i < nparent; ++i) {
			cmp = tree_entry_pathcmp(&tp[i], &tp[imin]);
			if (cmp < 0) {
				imin = i;
				tp[i].entry.mode &= ~S_IFXMIN_NEQ;
			}
			else if (cmp == 0) {
				tp[i].entry.mode &= ~S_IFXMIN_NEQ;
			}
			else {
				tp[i].entry.mode |= S_IFXMIN_NEQ;
			}
		}

		/* fixup markings for entries before imin */
		for (i = 0; i < imin; ++i)
			tp[i].entry.mode |= S_IFXMIN_NEQ;	/* pi > p[imin] */



		/* compare t vs p[imin] */
		cmp = tree_entry_pathcmp(&t, &tp[imin]);

		/* t = p[imin] */
		if (cmp == 0) {
			/* are either pi > p[imin] or diff(t,pi) != ø ? */
			if (!DIFF_OPT_TST(opt, FIND_COPIES_HARDER)) {
				for (i = 0; i < nparent; ++i) {
					/* p[i] > p[imin] */
					if (tp[i].entry.mode & S_IFXMIN_NEQ)
						continue;

					/* diff(t,pi) != ø */
					if (oidcmp(t.entry.oid, tp[i].entry.oid) ||
					    (t.entry.mode != tp[i].entry.mode))
						continue;

					goto skip_emit_t_tp;
				}
			}

			/* D += {δ(t,pi) if pi=p[imin];  "+a" if pi > p[imin]} */
			p = emit_path(p, base, opt, nparent,
					&t, tp, imin);

		skip_emit_t_tp:
			/* t↓,  ∀ pi=p[imin]  pi↓ */
			update_tree_entry(&t);
			update_tp_entries(tp, nparent);
		}

		/* t < p[imin] */
		else if (cmp < 0) {
			/* D += "+t" */
			p = emit_path(p, base, opt, nparent,
					&t, /*tp=*/NULL, -1);

			/* t↓ */
			update_tree_entry(&t);
		}

		/* t > p[imin] */
		else {
			/* ∀i pi=p[imin] -> D += "-p[imin]" */
			if (!DIFF_OPT_TST(opt, FIND_COPIES_HARDER)) {
				for (i = 0; i < nparent; ++i)
					if (tp[i].entry.mode & S_IFXMIN_NEQ)
						goto skip_emit_tp;
			}

			p = emit_path(p, base, opt, nparent,
					/*t=*/NULL, tp, imin);

		skip_emit_tp:
			/* ∀ pi=p[imin]  pi↓ */
			update_tp_entries(tp, nparent);
		}
	}

	free(ttree);
	for (i = nparent-1; i >= 0; i--)
		free(tptree[i]);
	FAST_ARRAY_FREE(tptree, nparent);
	FAST_ARRAY_FREE(tp, nparent);

	return p;
}