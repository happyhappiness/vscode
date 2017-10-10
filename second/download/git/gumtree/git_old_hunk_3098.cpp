	 * don't allow an offset too close to the end of the file.
	 */
	if (!p->pack_size && p->pack_fd == -1 && open_packed_git(p))
		die("packfile %s cannot be accessed", p->pack_name);
	if (offset > (p->pack_size - 20))
		die("offset beyond end of packfile (truncated pack?)");

	if (!win || !in_window(win, offset)) {
		if (win)
			win->inuse_cnt--;
		for (win = p->windows; win; win = win->next) {
			if (in_window(win, offset))
