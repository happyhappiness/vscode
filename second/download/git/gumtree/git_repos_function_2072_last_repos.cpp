static int show_modified(struct rev_info *revs,
			 const struct cache_entry *old,
			 const struct cache_entry *new,
			 int report_missing,
			 int cached, int match_missing)
{
	unsigned int mode, oldmode;
	const struct object_id *oid;
	unsigned dirty_submodule = 0;

	if (get_stat_data(new, &oid, &mode, cached, match_missing,
			  &dirty_submodule, &revs->diffopt) < 0) {
		if (report_missing)
			diff_index_show_file(revs, "-", old,
					     &old->oid, 1, old->ce_mode,
					     0);
		return -1;
	}

	if (revs->combine_merges && !cached &&
	    (oidcmp(oid, &old->oid) || oidcmp(&old->oid, &new->oid))) {
		struct combine_diff_path *p;
		int pathlen = ce_namelen(new);

		p = xmalloc(combine_diff_path_size(2, pathlen));
		p->path = (char *) &p->parent[2];
		p->next = NULL;
		memcpy(p->path, new->name, pathlen);
		p->path[pathlen] = 0;
		p->mode = mode;
		oidclr(&p->oid);
		memset(p->parent, 0, 2 * sizeof(struct combine_diff_parent));
		p->parent[0].status = DIFF_STATUS_MODIFIED;
		p->parent[0].mode = new->ce_mode;
		oidcpy(&p->parent[0].oid, &new->oid);
		p->parent[1].status = DIFF_STATUS_MODIFIED;
		p->parent[1].mode = old->ce_mode;
		oidcpy(&p->parent[1].oid, &old->oid);
		show_combined_diff(p, 2, revs->dense_combined_merges, revs);
		free(p);
		return 0;
	}

	oldmode = old->ce_mode;
	if (mode == oldmode && !oidcmp(oid, &old->oid) && !dirty_submodule &&
	    !DIFF_OPT_TST(&revs->diffopt, FIND_COPIES_HARDER))
		return 0;

	diff_change(&revs->diffopt, oldmode, mode,
		    &old->oid, oid, 1, !is_null_oid(oid),
		    old->name, 0, dirty_submodule);
	return 0;
}