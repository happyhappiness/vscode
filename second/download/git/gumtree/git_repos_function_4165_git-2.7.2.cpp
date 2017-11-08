static void do_add_man_viewer_info(const char *name,
				   size_t len,
				   const char *value)
{
	struct man_viewer_info_list *new = xcalloc(1, sizeof(*new) + len + 1);

	memcpy(new->name, name, len); /* NUL-terminated by xcalloc */
	new->info = xstrdup(value);
	new->next = man_viewer_info_list;
	man_viewer_info_list = new;
}