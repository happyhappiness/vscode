static struct ref_entry *create_dir_entry(struct files_ref_store *ref_store,
					  const char *dirname, size_t len,
					  int incomplete)
{
	struct ref_entry *direntry;
	FLEX_ALLOC_MEM(direntry, name, dirname, len);
	direntry->u.subdir.ref_store = ref_store;
	direntry->flag = REF_DIR | (incomplete ? REF_INCOMPLETE : 0);
	return direntry;
}