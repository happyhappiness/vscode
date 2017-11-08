static void add_sought_entry(struct ref ***sought, int *nr, int *alloc,
			     const char *string)
{
	add_sought_entry_mem(sought, nr, alloc, string, strlen(string));
}