static void do_remove_scheduled_dirs(int new_len)
{
	while (removal.len > new_len) {
		removal.path[removal.len] = '\0';
		if (rmdir(removal.path))
			break;
		do {
			removal.len--;
		} while (removal.len > new_len &&
			 removal.path[removal.len] != '/');
	}
	removal.len = new_len;
}