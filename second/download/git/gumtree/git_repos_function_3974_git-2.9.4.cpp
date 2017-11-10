static void strip_extension(const char **argv)
{
	size_t len;

	if (strip_suffix(argv[0], STRIP_EXTENSION, &len))
		argv[0] = xmemdupz(argv[0], len);
}