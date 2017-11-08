void add_exclude_line(struct exclude_struct ***listp,
		      const char *line, int include)
{
	char *tok, *p;
	if (!line || !*line) return;
	p = strdup(line);
	if (!p) out_of_memory("add_exclude_line");
	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
		add_exclude(listp, tok, include);
	free(p);
}