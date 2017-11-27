static inline int hlist_unhashed(const struct hlist_node *h)
{
	return !h->pprev;
}