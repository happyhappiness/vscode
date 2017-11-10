static inline void close_pair(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}