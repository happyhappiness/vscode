static struct diff_filepair *combined_pair(struct combine_diff_path *p,
					   int num_parent)
{
	int i;
	struct diff_filepair *pair;
	struct diff_filespec *pool;

	pair = xmalloc(sizeof(*pair));
	pool = xcalloc(st_add(num_parent, 1), sizeof(struct diff_filespec));
	pair->one = pool + 1;
	pair->two = pool;

	for (i = 0; i < num_parent; i++) {
		pair->one[i].path = p->path;
		pair->one[i].mode = p->parent[i].mode;
		oidcpy(&pair->one[i].oid, &p->parent[i].oid);
		pair->one[i].oid_valid = !is_null_oid(&p->parent[i].oid);
		pair->one[i].has_more_entries = 1;
	}
	pair->one[num_parent - 1].has_more_entries = 0;

	pair->two->path = p->path;
	pair->two->mode = p->mode;
	oidcpy(&pair->two->oid, &p->oid);
	pair->two->oid_valid = !is_null_oid(&p->oid);
	return pair;
}