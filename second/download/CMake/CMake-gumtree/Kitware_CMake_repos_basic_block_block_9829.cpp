{
	struct tree_entry *te;

	for (te = t->current->parent; te != NULL; te = te->parent) {
		if (te->dev == (int64_t)st->st_dev &&
		    te->ino == (int64_t)st->st_ino)
			return (1);
	}
	return (0);
}