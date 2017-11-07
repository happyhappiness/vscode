struct notes_tree **load_notes_trees(struct string_list *refs)
{
	struct string_list_item *item;
	int counter = 0;
	struct notes_tree **trees;
	trees = xmalloc((refs->nr+1) * sizeof(struct notes_tree *));
	for_each_string_list_item(item, refs) {
		struct notes_tree *t = xcalloc(1, sizeof(struct notes_tree));
		init_notes(t, item->string, combine_notes_ignore, 0);
		trees[counter++] = t;
	}
	trees[counter] = NULL;
	return trees;
}