static void child_dup2(int fd, int to)
{
	if (dup2(fd, to) < 0)
		child_die(CHILD_ERR_DUP2);
}