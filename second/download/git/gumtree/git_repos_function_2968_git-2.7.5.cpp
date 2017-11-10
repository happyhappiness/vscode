static inline int weight(struct commit_list *elem)
{
	return *((int*)(elem->item->util));
}