static void add_to_known_names(const char *path,
			       const unsigned char *peeled,
			       int prio,
			       const unsigned char *sha1)
{
	struct commit_name *e = find_commit_name(peeled);
	struct tag *tag = NULL;
	if (replace_name(e, prio, sha1, &tag)) {
		if (!e) {
			e = xmalloc(sizeof(struct commit_name));
			hashcpy(e->peeled, peeled);
			hashmap_entry_init(e, sha1hash(peeled));
			hashmap_add(&names, e);
			e->path = NULL;
		}
		e->tag = tag;
		e->prio = prio;
		e->name_checked = 0;
		hashcpy(e->sha1, sha1);
		free(e->path);
		e->path = xstrdup(path);
	}
}