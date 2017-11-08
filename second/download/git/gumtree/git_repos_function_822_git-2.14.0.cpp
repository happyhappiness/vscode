int wildmatch(const char *pattern, const char *text, unsigned int flags)
{
	return dowild((const uchar*)pattern, (const uchar*)text, flags);
}