static int anti_reference(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	show_rev(REVERSED, sha1, refname);
	return 0;
}