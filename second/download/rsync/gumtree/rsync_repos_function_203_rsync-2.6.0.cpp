static int safe_read(int desc, char *ptr, size_t len)
{
	int n_chars;
 
	if (len == 0)
		return len;
 
#ifdef EINTR
	do {
		n_chars = read(desc, ptr, len);
	} while (n_chars < 0 && errno == EINTR);
#else
	n_chars = read(desc, ptr, len);
#endif
 
	return n_chars;
}