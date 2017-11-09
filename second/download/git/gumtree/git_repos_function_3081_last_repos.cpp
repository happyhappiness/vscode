static int find_trailer_end(const char *buf, size_t len)
{
	return len - ignore_non_trailer(buf, len);
}