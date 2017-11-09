static inline void print_verbose(const struct fetch_pack_args *args,
				 const char *fmt, ...)
{
	va_list params;

	if (!args->verbose)
		return;

	va_start(params, fmt);
	vfprintf(stderr, fmt, params);
	va_end(params);
	fputc('\n', stderr);
}