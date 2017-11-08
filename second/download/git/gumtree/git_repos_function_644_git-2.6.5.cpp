int wildmatch(const char *pattern, const char *text,
	      unsigned int flags, struct wildopts *wo)
{
	return dowild((const uchar*)pattern, (const uchar*)text, flags);
}