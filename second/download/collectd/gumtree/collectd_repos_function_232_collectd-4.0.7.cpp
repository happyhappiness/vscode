char *sstrerror (int errnum, char *buf, size_t buflen)
{
	buf[0] = '\0';
	strerror_r (errnum, buf, buflen);
	return (buf);
}