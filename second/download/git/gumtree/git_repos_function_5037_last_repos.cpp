static int run_gpg_verify(const struct object_id *oid, const char *buf, unsigned long size, unsigned flags)
{
	struct signature_check signature_check;
	int ret;

	memset(&signature_check, 0, sizeof(signature_check));

	ret = check_commit_signature(lookup_commit(oid), &signature_check);
	print_signature_buffer(&signature_check, flags);

	signature_check_clear(&signature_check);
	return ret;
}