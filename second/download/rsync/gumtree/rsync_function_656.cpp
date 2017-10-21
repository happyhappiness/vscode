void add_include_line(char *p)
{
	char *tok;
	if (!p || !*p) return;
	p = strdup(p);
	if (!p) out_of_memory("add_include_line");
	for (tok=strtok(p," "); tok; tok=strtok(NULL," "))
		add_exclude(tok, 1);
	free(p);
}