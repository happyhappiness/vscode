static void show_suffix(int depth, const unsigned char *sha1)
{
	printf("-%d-g%s", depth, find_unique_abbrev(sha1, abbrev));
}