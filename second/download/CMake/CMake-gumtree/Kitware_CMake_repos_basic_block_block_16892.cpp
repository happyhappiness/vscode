{
		file->parent = file;
		if (mtree->root != NULL) {
			np = mtree->root;
			goto same_entry;
		}
		mtree->root = file;
		mtree_entry_register_add(mtree, file);
		return (ARCHIVE_OK);
	}