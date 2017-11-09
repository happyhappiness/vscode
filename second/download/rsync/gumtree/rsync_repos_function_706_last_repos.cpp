void
set_blocking(int fd)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
	return;
    if (val & NONBLOCK_FLAG) {
	val &= ~NONBLOCK_FLAG;
	fcntl(fd, F_SETFL, val);
    }
}