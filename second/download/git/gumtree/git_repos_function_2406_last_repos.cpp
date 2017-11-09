static void add_to_ref_list(const struct object_id *oid, const char *name,
		struct ref_list *list)
{
	ALLOC_GROW(list->list, list->nr + 1, list->alloc);
	oidcpy(&list->list[list->nr].oid, oid);
	list->list[list->nr].name = xstrdup(name);
	list->nr++;
}