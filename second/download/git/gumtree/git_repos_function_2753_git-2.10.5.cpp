static void debug_unpack_callback(int n,
				  unsigned long mask,
				  unsigned long dirmask,
				  struct name_entry *names,
				  struct traverse_info *info)
{
	int i;
	printf("* unpack mask %lu, dirmask %lu, cnt %d ",
	       mask, dirmask, n);
	debug_path(info);
	putchar('\n');
	for (i = 0; i < n; i++)
		debug_name_entry(i, names + i);
}