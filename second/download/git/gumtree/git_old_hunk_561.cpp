
static void entry_extract(struct tree_desc *t, struct name_entry *a)
{
	*a = t->entry;
}

void update_tree_entry(struct tree_desc *desc)
{
	const void *buf = desc->buffer;
	const unsigned char *end = desc->entry.oid->hash + 20;
	unsigned long size = desc->size;
	unsigned long len = end - (const unsigned char *)buf;

	if (size < len)
		die("corrupt tree file");
	buf = end;
	size -= len;
	desc->buffer = buf;
	desc->size = size;
	if (size)
		decode_tree_entry(desc, buf, size);
}

int tree_entry(struct tree_desc *desc, struct name_entry *entry)
{
	if (!desc->size)
		return 0;

	*entry = desc->entry;
	update_tree_entry(desc);
	return 1;
}

void setup_traverse_info(struct traverse_info *info, const char *base)
{
	int pathlen = strlen(base);
	static struct traverse_info dummy;

	memset(info, 0, sizeof(*info));
