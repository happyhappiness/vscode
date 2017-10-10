	va_start(vp, fmt);
	vprintf(fmt, vp);
	putchar('\n');
	va_end(vp);
}

static int mark_ce_flags(const char *path, int flag, int mark)
{
	int namelen = strlen(path);
	int pos = cache_name_pos(path, namelen);
	if (0 <= pos) {
		if (mark)
