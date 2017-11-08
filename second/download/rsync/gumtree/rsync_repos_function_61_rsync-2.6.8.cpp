static struct idlist *add_to_list(struct idlist **root, int id, char *name,
				  int id2)
{
	struct idlist *node = new(struct idlist);
	if (!node)
		out_of_memory("add_to_list");
	node->next = *root;
	node->name = name;
	node->id = id;
	node->id2 = id2;
	*root = node;
	return node;
}