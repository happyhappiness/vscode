static void add_left_or_right(struct hashmap *map, const char *path,
			      const char *content, int is_right)
{
	struct pair_entry *e, *existing;

	FLEX_ALLOC_STR(e, path, path);
	hashmap_entry_init(e, strhash(path));
	existing = hashmap_get(map, e, NULL);
	if (existing) {
		free(e);
		e = existing;
	} else {
		e->left[0] = e->right[0] = '\0';
		hashmap_add(map, e);
	}
	strlcpy(is_right ? e->right : e->left, content, PATH_MAX);
}