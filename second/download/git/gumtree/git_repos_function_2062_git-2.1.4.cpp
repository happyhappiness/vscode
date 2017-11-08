int close_lock_file(struct lock_file *lk)
{
	int fd = lk->fd;
	lk->fd = -1;
	return close(fd);
}