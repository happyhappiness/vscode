static void remove_from_list(struct trailer_item *item,
			     struct trailer_item **first,
			     struct trailer_item **last)
{
	struct trailer_item *next = item->next;
	struct trailer_item *previous = item->previous;

	if (next) {
		item->next->previous = previous;
		item->next = NULL;
	} else if (last)
		*last = previous;

	if (previous) {
		item->previous->next = next;
		item->previous = NULL;
	} else if (first)
		*first = next;
}