static void child_close(int fd)
{
	if (close(fd))
		child_die(CHILD_ERR_CLOSE);
}