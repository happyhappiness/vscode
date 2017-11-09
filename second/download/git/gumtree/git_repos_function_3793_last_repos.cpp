static struct stage_data *insert_stage_data(const char *path,
		struct tree *o, struct tree *a, struct tree *b,
		struct string_list *entries)
{
	struct string_list_item *item;
	struct stage_data *e = xcalloc(1, sizeof(struct stage_data));
	get_tree_entry(o->object.oid.hash, path,
			e->stages[1].oid.hash, &e->stages[1].mode);
	get_tree_entry(a->object.oid.hash, path,
			e->stages[2].oid.hash, &e->stages[2].mode);
	get_tree_entry(b->object.oid.hash, path,
			e->stages[3].oid.hash, &e->stages[3].mode);
	item = string_list_insert(entries, path);
	item->util = e;
	return e;
}