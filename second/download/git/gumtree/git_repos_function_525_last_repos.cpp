static void insert_file_table(struct hashmap *table, int index, struct diff_filespec *filespec)
{
	struct file_similarity *entry = xmalloc(sizeof(*entry));

	entry->index = index;
	entry->filespec = filespec;

	hashmap_entry_init(entry, hash_filespec(filespec));
	hashmap_add(table, entry);
}