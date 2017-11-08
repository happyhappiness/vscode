static int show_one_alternate_sha1(const unsigned char sha1[20], void *unused)
{
	show_ref(".have", sha1);
	return 0;
}