static inline void list_del_init(struct list_head *elem)
{
	list_del(elem);
	INIT_LIST_HEAD(elem);
}