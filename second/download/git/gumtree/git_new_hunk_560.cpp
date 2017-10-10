		mode = (mode << 3) + (c - '0');
	}
	*modep = mode;
	return str;
}

static int decode_tree_entry(struct tree_desc *desc, const char *buf, unsigned long size, struct strbuf *err)
{
	const char *path;
	unsigned int mode, len;

	if (size < 23 || buf[size - 21]) {
		strbuf_addstr(err, _("too-short tree object"));
		return -1;
	}

	path = get_mode(buf, &mode);
	if (!path) {
		strbuf_addstr(err, _("malformed mode in tree entry"));
		return -1;
	}
	if (!*path) {
		strbuf_addstr(err, _("empty filename in tree entry"));
		return -1;
	}
	len = strlen(path) + 1;

	/* Initialize the descriptor entry */
	desc->entry.path = path;
	desc->entry.mode = canon_mode(mode);
	desc->entry.oid  = (const struct object_id *)(path + len);

	return 0;
}

static int init_tree_desc_internal(struct tree_desc *desc, const void *buffer, unsigned long size, struct strbuf *err)
{
	desc->buffer = buffer;
	desc->size = size;
	if (size)
		return decode_tree_entry(desc, buffer, size, err);
	return 0;
}

void init_tree_desc(struct tree_desc *desc, const void *buffer, unsigned long size)
{
	struct strbuf err = STRBUF_INIT;
	if (init_tree_desc_internal(desc, buffer, size, &err))
		die("%s", err.buf);
	strbuf_release(&err);
}

int init_tree_desc_gently(struct tree_desc *desc, const void *buffer, unsigned long size)
{
	struct strbuf err = STRBUF_INIT;
	int result = init_tree_desc_internal(desc, buffer, size, &err);
	if (result)
		error("%s", err.buf);
	strbuf_release(&err);
	return result;
}

void *fill_tree_descriptor(struct tree_desc *desc, const unsigned char *sha1)
{
	unsigned long size = 0;
	void *buf = NULL;
