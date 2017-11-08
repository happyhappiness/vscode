int color_fprintf_ln(FILE *fp, const char *color, const char *fmt, ...)
{
	va_list args;
	int r;
	va_start(args, fmt);
	r = color_vfprintf(fp, color, fmt, args, "\n");
	va_end(args);
	return r;
}