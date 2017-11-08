static void add_man_viewer(const char *name)
{
	struct man_viewer_list **p = &man_viewer_list;

	while (*p)
		p = &((*p)->next);
	FLEX_ALLOC_STR(*p, name, name);
}