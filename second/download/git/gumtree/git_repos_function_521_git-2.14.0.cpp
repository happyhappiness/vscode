static unsigned int hash_filespec(struct diff_filespec *filespec)
{
	if (!filespec->oid_valid) {
		if (diff_populate_filespec(filespec, 0))
			return 0;
		hash_sha1_file(filespec->data, filespec->size, "blob",
			       filespec->oid.hash);
	}
	return sha1hash(filespec->oid.hash);
}