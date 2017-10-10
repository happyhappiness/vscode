
	va_start(params, err);
	die_routine(err, params);
	va_end(params);
}

void NORETURN die_errno(const char *fmt, ...)
{
	va_list params;
	char fmt_with_err[1024];
	char str_error[256], *err;
	int i, j;

	if (die_is_recursing()) {
		fputs("fatal: recursion detected in die_errno handler\n",
			stderr);
		exit(128);
	}

	err = strerror(errno);
	for (i = j = 0; err[i] && j < sizeof(str_error) - 1; ) {
		if ((str_error[j++] = err[i++]) != '%')
			continue;
		if (j < sizeof(str_error) - 1) {
			str_error[j++] = '%';
