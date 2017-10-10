			strbuf_addch(sb, '/');
		free(cwd);
	}
	strbuf_addstr(sb, path);
}

void strbuf_add_real_path(struct strbuf *sb, const char *path)
{
	if (sb->len) {
		struct strbuf resolved = STRBUF_INIT;
		strbuf_realpath(&resolved, path, 1);
		strbuf_addbuf(sb, &resolved);
		strbuf_release(&resolved);
	} else
		strbuf_realpath(sb, path, 1);
}

int printf_ln(const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
