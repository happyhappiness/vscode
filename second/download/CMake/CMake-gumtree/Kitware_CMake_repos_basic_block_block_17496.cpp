{
	struct file *file;
	static const struct archive_rb_tree_ops rb_ops = {
		file_cmp_node, file_cmp_key
	};

	file = calloc(1, sizeof(*file));
	if (file == NULL)
		return (NULL);

	if (entry != NULL)
		file->entry = archive_entry_clone(entry);
	else
		file->entry = archive_entry_new2(&a->archive);
	if (file->entry == NULL) {
		free(file);
		return (NULL);
	}
	__archive_rb_tree_init(&(file->rbtree), &rb_ops);
	file->children.first = NULL;
	file->children.last = &(file->children.first);
	file->xattr.first = NULL;
	file->xattr.last = &(file->xattr.first);
	archive_string_init(&(file->parentdir));
	archive_string_init(&(file->basename));
	archive_string_init(&(file->symlink));
	archive_string_init(&(file->script));
	if (entry != NULL && archive_entry_filetype(entry) == AE_IFDIR)
		file->dir = 1;

	return (file);
}