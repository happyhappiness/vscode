void *xmemdupz(const void *data, size_t len)
{
	return memcpy(xmallocz(len), data, len);
}