static inline void hlist_add_head_rcu(struct hlist_node *n,
					struct hlist_head *h)
{
	struct hlist_node *first = h->first;
	n->next = first;
	n->pprev = &h->first;
	smp_wmb();
	if (first)
		first->pprev = &n->next;
	h->first = n;
}