		mode = (mode << 3) + (c - '0');
	}
	*modep = mode;
	return str;
}

static void decode_tree_entry(struct tree_desc *desc, const char *buf, unsigned long size)
{
	const char *path;
	unsigned int mode, len;

	if (size < 24 || buf[size - 21])
		die("corrupt tree file");

	path = get_mode(buf, &mode);
	if (!path || !*path)
		die("corrupt tree file");
	len = strlen(path) + 1;

	/* Initialize the descriptor entry */
	desc->entry.path = path;
	desc->entry.mode = canon_mode(mode);
	desc->entry.oid  = (const struct object_id *)(path + len);
}

void init_tree_desc(struct tree_desc *desc, const void *buffer, unsigned long size)
{
	desc->buffer = buffer;
	desc->size = size;
	if (size)
		decode_tree_entry(desc, buffer, size);
}

void *fill_tree_descriptor(struct tree_desc *desc, const unsigned char *sha1)
{
	unsigned long size = 0;
	void *buf = NULL;
