static inline void
free_xbuf(xbuf *xb)
{
	if (xb->buf)
		free(xb->buf);
	memset(xb, 0, sizeof (xbuf));
}