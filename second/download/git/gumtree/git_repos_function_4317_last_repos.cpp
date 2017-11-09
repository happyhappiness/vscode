static void std_output(struct grep_opt *opt, const void *buf, size_t size)
{
	fwrite(buf, size, 1, stdout);
}