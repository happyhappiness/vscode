static inline void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
	SWAP(*a, *b);
}