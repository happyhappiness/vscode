void color_set(char *dst, const char *color_bytes)
{
	xsnprintf(dst, COLOR_MAXLEN, "%s", color_bytes);
}