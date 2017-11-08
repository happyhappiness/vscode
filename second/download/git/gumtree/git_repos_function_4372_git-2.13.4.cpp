static inline uInt zlib_buf_cap(unsigned long len)
{
	return (ZLIB_BUF_MAX < len) ? ZLIB_BUF_MAX : len;
}