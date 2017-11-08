struct sha1file *sha1fd(int fd, const char *name)
{
	return sha1fd_throughput(fd, name, NULL);
}