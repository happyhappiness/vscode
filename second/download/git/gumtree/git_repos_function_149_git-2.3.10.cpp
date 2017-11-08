static int check_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	mark_our_ref(refname, sha1);
	return 0;
}