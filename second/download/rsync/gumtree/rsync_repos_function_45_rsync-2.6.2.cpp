void recv_exclude_list(int f)
{
	char line[MAXPATHLEN+1]; /* Allows a trailing slash on a max-len dir */
	unsigned int l;

	while ((l = read_int(f)) != 0) {
		if (l >= sizeof line)
			overflow("recv_exclude_list");
		read_sbuf(f, line, l);
		add_exclude(&exclude_list, line, 0);
	}
}