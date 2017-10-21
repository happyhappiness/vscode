extern int sanitize_paths;

static char topsrcname[MAXPATHLEN];

static struct exclude_struct **local_exclude_list;

static struct file_struct null_file;

static void clean_flist(struct file_list *flist, int strip_root);

struct string_area *string_area_new(int size)
{
	struct string_area *a;

	if (size <= 0) size = ARENA_SIZE;
	a = malloc(sizeof(*a));
	if (!a) out_of_memory("string_area_new");
	a->current = a->base = malloc(size);
	if (!a->current) out_of_memory("string_area_new buffer");
	a->end = a->base + size;
	a->next = 0;

	return a;
}

void string_area_free(struct string_area *a)
{
	struct string_area *next;

	for ( ; a ; a = next) {
		next = a->next;
		free(a->base);
	}
}

char *string_area_malloc(struct string_area **ap, int size)
{
	char *p;
	struct string_area *a;

	/* does the request fit into the current space? */
	a = *ap;
	if (a->current + size >= a->end) {
		/* no; get space, move new string_area to front of the list */
		a = string_area_new(size > ARENA_SIZE ? size : ARENA_SIZE);
		a->next = *ap;
		*ap = a;
	}

	/* have space; do the "allocation." */
	p = a->current;
	a->current += size;
	return p;
}

char *string_area_strdup(struct string_area **ap, const char *src)
{
	char* dest = string_area_malloc(ap, strlen(src) + 1);
	return strcpy(dest, src);
}

static void list_file_entry(struct file_struct *f)
{
	char perms[11] = "----------";
	char *perm_map = "rwxrwxrwx";
	int i;
