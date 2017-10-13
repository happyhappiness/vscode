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
		} else {
			/* No room to double the '%', so we overwrite it with
			 * '\0' below */
			j--;
			break;
		}
	}
	str_error[j] = 0;
	snprintf(fmt_with_err, sizeof(fmt_with_err), "%s: %s", fmt, str_error);

	va_start(params, fmt);
	die_routine(fmt_with_err, params);
	va_end(params);
}