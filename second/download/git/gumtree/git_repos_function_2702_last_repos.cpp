void strbuf_expand(struct strbuf *sb, const char *format, expand_fn_t fn,
		   void *context)
{
	for (;;) {
		const char *percent;
		size_t consumed;

		percent = strchrnul(format, '%');
		strbuf_add(sb, format, percent - format);
		if (!*percent)
			break;
		format = percent + 1;

		if (*format == '%') {
			strbuf_addch(sb, '%');
			format++;
			continue;
		}

		consumed = fn(sb, format, context);
		if (consumed)
			format += consumed;
		else
			strbuf_addch(sb, '%');
	}
}