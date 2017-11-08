void recv_exclude_list(int f)
{
	char line[MAXPATHLEN];
	int l;
	while ((l=read_int(f))) {
		if (l >= MAXPATHLEN) overflow("recv_exclude_list");
		read_sbuf(f,line,l);
		add_exclude(line,0);
	}
}