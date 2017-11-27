static inline int hlist_empty(const struct hlist_head *h)
{
	return !h->first;
}