
static void entry_extract(struct tree_desc *t, struct name_entry *a)
{
	*a = t->entry;
}

static int update_tree_entry_internal(struct tree_desc *desc, struct strbuf *err)
{
	const void *buf = desc->buffer;
	const unsigned char *end = desc->entry.oid->hash + 20;
	unsigned long size = desc->size;
	unsigned long len = end - (const unsigned char *)buf;

	if (size < len)
		die(_("too-short tree file"));
	buf = end;
	size -= len;
	desc->buffer = buf;
	desc->size = size;
	if (size)
		return decode_tree_entry(desc, buf, size, err);
	return 0;
}

void update_tree_entry(struct tree_desc *desc)
{
	struct strbuf err = STRBUF_INIT;
	if (update_tree_entry_internal(desc, &err))
		die("%s", err.buf);
	strbuf_release(&err);
}

int update_tree_entry_gently(struct tree_desc *desc)
{
	struct strbuf err = STRBUF_INIT;
	if (update_tree_entry_internal(desc, &err)) {
		error("%s", err.buf);
		strbuf_release(&err);
		/* Stop processing this tree after error */
		desc->size = 0;
		return -1;
	}
	strbuf_release(&err);
	return 0;
}

int tree_entry(struct tree_desc *desc, struct name_entry *entry)
{
	if (!desc->size)
		return 0;

	*entry = desc->entry;
	update_tree_entry(desc);
	return 1;
}

int tree_entry_gently(struct tree_desc *desc, struct name_entry *entry)
{
	if (!desc->size)
		return 0;

	*entry = desc->entry;
	if (update_tree_entry_gently(desc))
		return 0;
	return 1;
}

void setup_traverse_info(struct traverse_info *info, const char *base)
{
	int pathlen = strlen(base);
	static struct traverse_info dummy;

	memset(info, 0, sizeof(*info));
