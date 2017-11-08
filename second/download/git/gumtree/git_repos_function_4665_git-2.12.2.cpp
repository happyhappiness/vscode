static void do_add_man_viewer_info(const char *name,
				   size_t len,
				   const char *value)
{
	struct man_viewer_info_list *new;
	FLEX_ALLOC_MEM(new, name, name, len);
	new->info = xstrdup(value);
	new->next = man_viewer_info_list;
	man_viewer_info_list = new;
}