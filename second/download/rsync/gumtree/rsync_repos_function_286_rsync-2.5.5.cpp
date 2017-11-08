static void string_area_free(struct string_area *a)
{
	struct string_area *next;

	for (; a; a = next) {
		next = a->next;
		free(a->base);
	}
}