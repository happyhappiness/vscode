static inline void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
	struct strbuf tmp = *a;
	*a = *b;
	*b = tmp;
}