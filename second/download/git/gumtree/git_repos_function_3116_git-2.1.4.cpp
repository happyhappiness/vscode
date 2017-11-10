static int reject_entry(const unsigned char *sha1, const char *base,
			int baselen, const char *filename, unsigned mode,
			int stage, void *context)
{
	return -1;
}