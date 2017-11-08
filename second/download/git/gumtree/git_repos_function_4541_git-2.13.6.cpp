static void strip_submodule_slash_cheap(struct pathspec_item *item)
{
	if (item->len >= 1 && item->match[item->len - 1] == '/') {
		int i = cache_name_pos(item->match, item->len - 1);

		if (i >= 0 && S_ISGITLINK(active_cache[i]->ce_mode)) {
			item->len--;
			item->match[item->len] = '\0';
		}
	}
}