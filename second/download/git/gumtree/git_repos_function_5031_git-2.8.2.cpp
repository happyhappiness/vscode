static int head_has_history(void)
{
	unsigned char sha1[20];

	return !get_sha1("HEAD", sha1);
}