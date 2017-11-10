static void anonymize_path(struct strbuf *out, const char *path,
			   struct hashmap *map,
			   void *(*generate)(const void *, size_t *))
{
	while (*path) {
		const char *end_of_component = strchrnul(path, '/');
		size_t len = end_of_component - path;
		const char *c = anonymize_mem(map, generate, path, &len);
		strbuf_add(out, c, len);
		path = end_of_component;
		if (*path)
			strbuf_addch(out, *path++);
	}
}