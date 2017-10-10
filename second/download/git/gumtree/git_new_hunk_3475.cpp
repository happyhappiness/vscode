			 * '\0' below */
			j--;
			break;
		}
	}
	str_error[j] = 0;
	snprintf(buf, n, "%s: %s", fmt, str_error);
	return buf;
}

void NORETURN die_errno(const char *fmt, ...)
{
	char buf[1024];
	va_list params;

	if (die_is_recursing()) {
		fputs("fatal: recursion detected in die_errno handler\n",
			stderr);
		exit(128);
	}

	va_start(params, fmt);
	die_routine(fmt_with_err(buf, sizeof(buf), fmt), params);
	va_end(params);
}

int error_errno(const char *fmt, ...)
{
	char buf[1024];
	va_list params;

	va_start(params, fmt);
	error_routine(fmt_with_err(buf, sizeof(buf), fmt), params);
	va_end(params);
	return -1;
}

#undef error
int error(const char *err, ...)
{
	va_list params;
