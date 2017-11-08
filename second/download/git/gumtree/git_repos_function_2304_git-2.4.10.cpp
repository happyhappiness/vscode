static void free_all(struct trailer_item **first)
{
	while (*first) {
		struct trailer_item *item = remove_first(first);
		free_trailer_item(item);
	}
}