static void free_trailer_item(struct trailer_item *item)
{
	free(item->token);
	free(item->value);
	free(item);
}