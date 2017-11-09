static void prepare_show_merge(struct rev_info *revs)
{
	struct commit_list *bases;
	struct commit *head, *other;
	struct object_id oid;
	const char **prune = NULL;
	int i, prune_num = 1; /* counting terminating NULL */

	if (get_oid("HEAD", &oid))
		die("--merge without HEAD?");
	head = lookup_commit_or_die(&oid, "HEAD");
	if (get_oid("MERGE_HEAD", &oid))
		die("--merge without MERGE_HEAD?");
	other = lookup_commit_or_die(&oid, "MERGE_HEAD");
	add_pending_object(revs, &head->object, "HEAD");
	add_pending_object(revs, &other->object, "MERGE_HEAD");
	bases = get_merge_bases(head, other);
	add_rev_cmdline_list(revs, bases, REV_CMD_MERGE_BASE, UNINTERESTING | BOTTOM);
	add_pending_commit_list(revs, bases, UNINTERESTING | BOTTOM);
	free_commit_list(bases);
	head->object.flags |= SYMMETRIC_LEFT;

	if (!active_nr)
		read_cache();
	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];
		if (!ce_stage(ce))
			continue;
		if (ce_path_match(ce, &revs->prune_data, NULL)) {
			prune_num++;
			REALLOC_ARRAY(prune, prune_num);
			prune[prune_num-2] = ce->name;
			prune[prune_num-1] = NULL;
		}
		while ((i+1 < active_nr) &&
		       ce_same_name(ce, active_cache[i+1]))
			i++;
	}
	clear_pathspec(&revs->prune_data);
	parse_pathspec(&revs->prune_data, PATHSPEC_ALL_MAGIC & ~PATHSPEC_LITERAL,
		       PATHSPEC_PREFER_FULL | PATHSPEC_LITERAL_PATH, "", prune);
	revs->limited = 1;
}