static inline struct llist_item *llist_insert_back(struct llist *list,
						   const unsigned char *sha1)
{
	return llist_insert(list, list->back, sha1);
}