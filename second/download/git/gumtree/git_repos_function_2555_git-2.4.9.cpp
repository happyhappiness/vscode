static struct ref_entry *create_dir_entry(struct ref_cache *ref_cache,
					  const char *dirname, size_t len,
					  int incomplete)
{
	struct ref_entry *direntry;
	direntry = xcalloc(1, sizeof(struct ref_entry) + len + 1);
	memcpy(direntry->name, dirname, len);
	direntry->name[len] = '\0';
	direntry->u.subdir.ref_cache = ref_cache;
	direntry->flag = REF_DIR | (incomplete ? REF_INCOMPLETE : 0);
	return direntry;
}