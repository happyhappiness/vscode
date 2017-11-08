struct exclude_list *add_exclude_list(struct dir_struct *dir,
				      int group_type, const char *src)
{
	struct exclude_list *el;
	struct exclude_list_group *group;

	group = &dir->exclude_list_group[group_type];
	ALLOC_GROW(group->el, group->nr + 1, group->alloc);
	el = &group->el[group->nr++];
	memset(el, 0, sizeof(*el));
	el->src = src;
	return el;
}