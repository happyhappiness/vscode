static void add_commit_info(struct commit *commit, void *util,
		struct commit_info_lifo *lifo)
{
	struct commit_info *info;
	ALLOC_GROW(lifo->items, lifo->nr + 1, lifo->alloc);
	info = lifo->items + lifo->nr;
	info->commit = commit;
	info->util = util;
	lifo->nr++;
}