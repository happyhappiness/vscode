static void *get_nth_next(void *list, unsigned long n,
			  void *(*get_next_fn)(const void *))
{
	while (n-- && list)
		list = get_next_fn(list);
	return list;
}