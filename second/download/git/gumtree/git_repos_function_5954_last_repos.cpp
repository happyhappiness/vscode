static inline struct llist_item *llist_insert_sorted_unique(struct llist *list,
			const unsigned char *sha1, struct llist_item *hint)
{
	struct llist_item *prev = NULL, *l;

	l = (hint == NULL) ? list->front : hint;
	while (l) {
		int cmp = hashcmp(l->sha1, sha1);
		if (cmp > 0) { /* we insert before this entry */
			return llist_insert(list, prev, sha1);
		}
		if (!cmp) { /* already exists */
			return l;
		}
		prev = l;
		l = l->next;
	}
	/* insert at the end */
	return llist_insert_back(list, sha1);
}