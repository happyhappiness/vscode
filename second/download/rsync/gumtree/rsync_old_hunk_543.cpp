		if (l >= MAXPATHLEN) overflow("recv_exclude_list");
		read_sbuf(f,line,l);
		add_exclude(line,0);
	}
}


void add_exclude_line(char *p)
{
	char *tok;
	if (!p || !*p) return;
	p = strdup(p);
	if (!p) out_of_memory("add_exclude_line");
	for (tok=strtok(p," "); tok; tok=strtok(NULL," "))
		add_exclude(tok, 0);
	free(p);
}

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


static char *cvs_ignore_list[] = {
