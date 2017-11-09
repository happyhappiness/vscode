LAST_ARG_MUST_BE_NULL
static void verify_opt_compatible(const char *me, const char *base_opt, ...)
{
	const char *this_opt;
	va_list ap;

	va_start(ap, base_opt);
	while ((this_opt = va_arg(ap, const char *))) {
		if (va_arg(ap, int))
			break;
	}
	va_end(ap);

	if (this_opt)
		die(_("%s: %s cannot be used with %s"), me, this_opt, base_opt);
}