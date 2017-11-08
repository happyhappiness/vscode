static inline void
realloc_xbuf(xbuf *xb, size_t sz)
{
	char *bf = realloc_array(xb->buf, char, sz);
	if (!bf)
		out_of_memory("realloc_xbuf");
	xb->buf = bf;
	xb->size = sz;
}