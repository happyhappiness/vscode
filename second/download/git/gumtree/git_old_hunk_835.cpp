			strbuf_addch(sb, '/');
		free(cwd);
	}
	strbuf_addstr(sb, path);
}

int printf_ln(const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
