static void load_all_objects(void)
{
	struct pack_list *pl = local_packs;
	struct llist_item *hint, *l;

	llist_init(&all_objects);

	while (pl) {
		hint = NULL;
		l = pl->all_objects->front;
		while (l) {
			hint = llist_insert_sorted_unique(all_objects,
							  l->sha1, hint);
			l = l->next;
		}
		pl = pl->next;
	}
	/* remove objects present in remote packs */
	pl = altodb_packs;
	while (pl) {
		llist_sorted_difference_inplace(all_objects, pl->all_objects);
		pl = pl->next;
	}
}