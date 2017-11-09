static void unresolved_directory(const struct traverse_info *info,
				 struct name_entry n[3])
{
	char *newbase;
	struct name_entry *p;
	struct tree_desc t[3];
	void *buf0, *buf1, *buf2;

	for (p = n; p < n + 3; p++) {
		if (p->mode && S_ISDIR(p->mode))
			break;
	}
	if (n + 3 <= p)
		return; /* there is no tree here */

	newbase = traverse_path(info, p);

#define ENTRY_SHA1(e) (((e)->mode && S_ISDIR((e)->mode)) ? (e)->oid->hash : NULL)
	buf0 = fill_tree_descriptor(t+0, ENTRY_SHA1(n + 0));
	buf1 = fill_tree_descriptor(t+1, ENTRY_SHA1(n + 1));
	buf2 = fill_tree_descriptor(t+2, ENTRY_SHA1(n + 2));
#undef ENTRY_SHA1

	merge_trees(t, newbase);

	free(buf0);
	free(buf1);
	free(buf2);
	free(newbase);
}