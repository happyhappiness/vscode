static int add_pending_uninteresting_ref(const char *refname,
					 const unsigned char *sha1,
					 int flags, void *cb_data)
{
	add_pending_sha1(cb_data, refname, sha1, UNINTERESTING);
	return 0;
}