static void drop_attr_stack(void)
{
	while (attr_stack) {
		struct attr_stack *elem = attr_stack;
		attr_stack = elem->prev;
		free_attr_elem(elem);
	}
}