static void free_array_item(struct ref_array_item *item)
{
	free((char *)item->symref);
	free(item);
}