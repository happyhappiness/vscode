static inline void
alloc_xbuf(xbuf *xb, size_t sz)
{
	if (!(xb->buf = new_array(char, sz)))
		out_of_memory("alloc_xbuf");
	xb->size = sz;
	xb->len = xb->pos = 0;
}