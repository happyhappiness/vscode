static void fsck_sha1_list(void)
{
	int i, nr = sha1_list.nr;

	if (SORT_DIRENT)
		qsort(sha1_list.entry, nr,
		      sizeof(struct sha1_entry *), ino_compare);
	for (i = 0; i < nr; i++) {
		struct sha1_entry *entry = sha1_list.entry[i];
		unsigned char *sha1 = entry->sha1;

		sha1_list.entry[i] = NULL;
		if (fsck_sha1(sha1))
			errors_found |= ERROR_OBJECT;
		free(entry);
	}
	sha1_list.nr = 0;
}