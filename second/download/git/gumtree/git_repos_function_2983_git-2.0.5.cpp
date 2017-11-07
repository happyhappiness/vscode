static int read_one_entry_quick(const unsigned char *sha1, const char *base, int baselen, const char *pathname, unsigned mode, int stage, void *context)
{
	return read_one_entry_opt(sha1, base, baselen, pathname, mode, stage,
				  ADD_CACHE_JUST_APPEND);
}