static void line_log_data_insert(struct line_log_data **list,
				 char *path,
				 long begin, long end)
{
	struct line_log_data *ip;
	struct line_log_data *p = search_line_log_data(*list, path, &ip);

	if (p) {
		range_set_append_unsafe(&p->ranges, begin, end);
		free(path);
		return;
	}

	p = xcalloc(1, sizeof(struct line_log_data));
	p->path = path;
	range_set_append(&p->ranges, begin, end);
	if (ip) {
		p->next = ip->next;
		ip->next = p;
	} else {
		p->next = *list;
		*list = p;
	}
}