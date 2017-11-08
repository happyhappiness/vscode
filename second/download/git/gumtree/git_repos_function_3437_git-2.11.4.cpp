static int check_has_commit(const unsigned char sha1[20], void *data)
{
	int *has_commit = data;

	if (!lookup_commit_reference(sha1))
		*has_commit = 0;

	return 0;
}