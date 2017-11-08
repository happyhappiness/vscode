void add_exclude_line(char *p)
{
	char *tok;
	if (!p || !*p) return;
	p = strdup(p);
	if (!p) out_of_memory("add_exclude_line");
 	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
		add_exclude(tok, 0);
	free(p);
}