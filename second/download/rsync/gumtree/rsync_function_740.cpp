static struct string_area *string_area_new(int size)
{
	struct string_area *a;

	if (size <= 0)
		size = ARENA_SIZE;
	a = new(struct string_area);
	if (!a)
		out_of_memory("string_area_new");
	a->current = a->base = new_array(char, size);
	if (!a->current)
		out_of_memory("string_area_new buffer");
	a->end = a->base + size;
	a->next = NULL;

	return a;
}