static void decref_split(struct blame_entry *split)
{
	int i;

	for (i = 0; i < 3; i++)
		origin_decref(split[i].suspect);
}