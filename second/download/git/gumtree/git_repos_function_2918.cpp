static void do_remove_scheduled_dirs(int new_len)
{
	while (removal.len > new_len) {
		removal.buf[removal.len] = '\0';
		if (rmdir(removal.buf))
			break;
		do {
			removal.len--;
		} while (removal.len > new_len &&
			 removal.buf[removal.len] != '/');
	}
	removal.len = new_len;
}