void read_stream_flags(int fd)
{
	batch_stream_flags = read_int(fd);
}