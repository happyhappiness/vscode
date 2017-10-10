			    x >> 10, ((x & ((1 << 10) - 1)) * 100) >> 10);
	} else {
		strbuf_addf(buf, "%u bytes", (int)bytes);
	}
}

int printf_ln(const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
