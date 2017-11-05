static int write_rr(struct string_list *rr, int out_fd)
{
	int i;
	for (i = 0; i < rr->nr; i++) {
		const char *path;
		int length;
		if (!rr->items[i].util)
			continue;
		path = rr->items[i].string;
		length = strlen(path) + 1;
		if (write_in_full(out_fd, rr->items[i].util, 40) != 40 ||
		    write_str_in_full(out_fd, "\t") != 1 ||
		    write_in_full(out_fd, path, length) != length)
			die("unable to write rerere record");
	}
	if (commit_lock_file(&write_lock) != 0)
		die("unable to write rerere record");
	return 0;
}