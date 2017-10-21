	if (!bf)
		out_of_memory("realloc_xbuf");
	xb->buf = bf;
	xb->size = sz;
}

static inline void
free_xbuf(xbuf *xb)
{
	if (xb->buf)
		free(xb->buf);
	memset(xb, 0, sizeof (xbuf));
}

static inline int
to_wire_mode(mode_t mode)
{
#ifdef SUPPORT_LINKS
#if _S_IFLNK != 0120000
	if (S_ISLNK(mode))
