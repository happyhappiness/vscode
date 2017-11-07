void vreportf(const char *prefix, const char *err, va_list params)
{
	FILE *fh = error_handle ? error_handle : stderr;

	fflush(fh);
	if (!tweaked_error_buffering) {
		setvbuf(fh, NULL, _IOLBF, 0);
		tweaked_error_buffering = 1;
	}

	fputs(prefix, fh);
	vfprintf(fh, err, params);
	fputc('\n', fh);
}