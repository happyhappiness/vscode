static struct exclude_struct **local_exclude_list;

static struct file_struct null_file;

static void clean_flist(struct file_list *flist, int strip_root);

static struct string_area *string_area_new(int size)
{
	struct string_area *a;

	if (size <= 0) size = ARENA_SIZE;
	a = malloc(sizeof(*a));
	if (!a) out_of_memory("string_area_new");
	a->current = a->base = malloc(size);
	if (!a->current) out_of_memory("string_area_new buffer");
	a->end = a->base + size;
	a->next = NULL;

	return a;
}

static void string_area_free(struct string_area *a)
{
	struct string_area *next;

	for ( ; a ; a = next) {
		next = a->next;
		free(a->base);
	}
}

static char *string_area_malloc(struct string_area **ap, int size)
{
	char *p;
	struct string_area *a;

	/* does the request fit into the current space? */
	a = *ap;
