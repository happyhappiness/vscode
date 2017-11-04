static void add_suffix(struct suffix_tree **prior, char ltr, const char *str)
{
	struct suffix_tree *node, *newnode;

	if (ltr == '[') {
		const char *after = strchr(str, ']');
		/* Just skip bogus character classes. */
		if (!after++)
			return;
		while ((ltr = *str++) != ']')
			add_suffix(prior, ltr, after);
		return;
	}

	for (node = *prior; node; prior = &node->sibling, node = node->sibling) {
		if (node->letter == ltr) {
			if (*str)
				add_suffix(&node->child, *str, str+1);
			else
				node->word_end = 1;
			return;
		}
		if (node->letter > ltr)
			break;
	}
	if (!(newnode = new(struct suffix_tree)))
		out_of_memory("add_suffix");
	newnode->sibling = node;
	newnode->child = NULL;
	newnode->letter = ltr;
	*prior = newnode;
	if (*str) {
		add_suffix(&newnode->child, *str, str+1);
		newnode->word_end = 0;
	} else
		newnode->word_end = 1;
}