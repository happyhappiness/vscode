static void add_to_ref_list(const unsigned char *sha1, const char *name,
		struct ref_list *list)
{
	ALLOC_GROW(list->list, list->nr + 1, list->alloc);
	hashcpy(list->list[list->nr].sha1, sha1);
	list->list[list->nr].name = xstrdup(name);
	list->nr++;
}