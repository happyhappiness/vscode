static struct cache_tree_sub *find_subtree(struct cache_tree *it,
					   const char *path,
					   int pathlen,
					   int create)
{
	struct cache_tree_sub *down;
	int pos = subtree_pos(it, path, pathlen);
	if (0 <= pos)
		return it->down[pos];
	if (!create)
		return NULL;

	pos = -pos-1;
	ALLOC_GROW(it->down, it->subtree_nr + 1, it->subtree_alloc);
	it->subtree_nr++;

	down = xmalloc(sizeof(*down) + pathlen + 1);
	down->cache_tree = NULL;
	down->namelen = pathlen;
	memcpy(down->name, path, pathlen);
	down->name[pathlen] = 0;

	if (pos < it->subtree_nr)
		memmove(it->down + pos + 1,
			it->down + pos,
			sizeof(down) * (it->subtree_nr - pos - 1));
	it->down[pos] = down;
	return down;
}