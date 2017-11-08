static void write_tree(unsigned char *sha1)
{
	struct strbuf buf;
	size_t size;
	int i;

	QSORT(entries, used, ent_compare);
	for (size = i = 0; i < used; i++)
		size += 32 + entries[i]->len;

	strbuf_init(&buf, size);
	for (i = 0; i < used; i++) {
		struct treeent *ent = entries[i];
		strbuf_addf(&buf, "%o %s%c", ent->mode, ent->name, '\0');
		strbuf_add(&buf, ent->sha1, 20);
	}

	write_sha1_file(buf.buf, buf.len, tree_type, sha1);
	strbuf_release(&buf);
}