static inline void weight_set(struct commit_list *elem, int weight)
{
	*((int*)(elem->item->util)) = weight;
}