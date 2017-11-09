int lock_range(int fd, int offset, int len)
{
	struct flock lock;

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = offset;
	lock.l_len = len;
	lock.l_pid = 0;

	return fcntl(fd,F_SETLK,&lock) == 0;
}