static void do_delayed_deletions(char *delbuf)
{
	int mode, flags;

	if (deldelay_fd >= 0) {
		if (deldelay_cnt && !flush_delete_delay())
			return;
		lseek(deldelay_fd, 0, 0);
	}
	while ((mode = read_delay_line(delbuf, &flags)) >= 0)
		delete_item(delbuf, mode, flags | DEL_RECURSE);
	if (deldelay_fd >= 0)
		close(deldelay_fd);
}