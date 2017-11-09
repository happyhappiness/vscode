static void child_close_pair(int fd[2])
{
	child_close(fd[0]);
	child_close(fd[1]);
}