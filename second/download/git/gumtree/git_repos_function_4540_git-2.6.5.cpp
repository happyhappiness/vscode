static int show_abbrev(const unsigned char *sha1, void *cb_data)
{
	show_rev(NORMAL, sha1, NULL);
	return 0;
}