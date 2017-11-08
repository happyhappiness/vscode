static unsigned int hash_filespec(struct diff_filespec *filespec)
{
	if (!filespec->sha1_valid) {
		if (diff_populate_filespec(filespec, 0))
			return 0;
		hash_sha1_file(filespec->data, filespec->size, "blob", filespec->sha1);
	}
	return sha1hash(filespec->sha1);
}