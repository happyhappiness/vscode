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