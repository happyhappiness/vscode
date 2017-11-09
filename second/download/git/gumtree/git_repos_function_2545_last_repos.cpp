static struct combine_diff_path *emit_path(struct combine_diff_path *p,
	struct strbuf *base, struct diff_options *opt, int nparent,
	struct tree_desc *t, struct tree_desc *tp,
	int imin)
{
	unsigned mode;
	const char *path;
	const struct object_id *oid;
	int pathlen;
	int old_baselen = base->len;
	int i, isdir, recurse = 0, emitthis = 1;

	/* at least something has to be valid */
	assert(t || tp);

	if (t) {
		/* path present in resulting tree */
		oid = tree_entry_extract(t, &path, &mode);
		pathlen = tree_entry_len(&t->entry);
		isdir = S_ISDIR(mode);
	} else {
		/*
		 * a path was removed - take path from imin parent. Also take
		 * mode from that parent, to decide on recursion(1).
		 *
		 * 1) all modes for tp[i]=tp[imin] should be the same wrt
		 *    S_ISDIR, thanks to base_name_compare().
		 */
		tree_entry_extract(&tp[imin], &path, &mode);
		pathlen = tree_entry_len(&tp[imin].entry);

		isdir = S_ISDIR(mode);
		oid = NULL;
		mode = 0;
	}

	if (DIFF_OPT_TST(opt, RECURSIVE) && isdir) {
		recurse = 1;
		emitthis = DIFF_OPT_TST(opt, TREE_IN_RECURSIVE);
	}

	if (emitthis) {
		int keep;
		struct combine_diff_path *pprev = p;
		p = path_appendnew(p, nparent, base, path, pathlen, mode, oid);

		for (i = 0; i < nparent; ++i) {
			/*
			 * tp[i] is valid, if present and if tp[i]==tp[imin] -
			 * otherwise, we should ignore it.
			 */
			int tpi_valid = tp && !(tp[i].entry.mode & S_IFXMIN_NEQ);

			const struct object_id *oid_i;
			unsigned mode_i;

			p->parent[i].status =
				!t ? DIFF_STATUS_DELETED :
					tpi_valid ?
						DIFF_STATUS_MODIFIED :
						DIFF_STATUS_ADDED;

			if (tpi_valid) {
				oid_i = tp[i].entry.oid;
				mode_i = tp[i].entry.mode;
			}
			else {
				oid_i = &null_oid;
				mode_i = 0;
			}

			p->parent[i].mode = mode_i;
			oidcpy(&p->parent[i].oid, oid_i);
		}

		keep = 1;
		if (opt->pathchange)
			keep = opt->pathchange(opt, p);

		/*
		 * If a path was filtered or consumed - we don't need to add it
		 * to the list and can reuse its memory, leaving it as
		 * pre-allocated element on the tail.
		 *
		 * On the other hand, if path needs to be kept, we need to
		 * correct its .next to NULL, as it was pre-initialized to how
		 * much memory was allocated.
		 *
		 * see path_appendnew() for details.
		 */
		if (!keep)
			p = pprev;
		else
			p->next = NULL;
	}

	if (recurse) {
		const struct object_id **parents_oid;

		FAST_ARRAY_ALLOC(parents_oid, nparent);
		for (i = 0; i < nparent; ++i) {
			/* same rule as in emitthis */
			int tpi_valid = tp && !(tp[i].entry.mode & S_IFXMIN_NEQ);

			parents_oid[i] = tpi_valid ? tp[i].entry.oid : NULL;
		}

		strbuf_add(base, path, pathlen);
		strbuf_addch(base, '/');
		p = ll_diff_tree_paths(p, oid, parents_oid, nparent, base, opt);
		FAST_ARRAY_FREE(parents_oid, nparent);
	}

	strbuf_setlen(base, old_baselen);
	return p;
}