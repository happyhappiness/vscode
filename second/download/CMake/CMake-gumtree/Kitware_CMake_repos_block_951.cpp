{
	struct xar *xar;
	va_list ap;

	xar = (struct xar *)a->format_data;
	va_start(ap, fmt);
	archive_string_empty(&xar->vstr);
	archive_string_vsprintf(&xar->vstr, fmt, ap);
	va_end(ap);
	return (xmlwrite_string(a, writer, key, xar->vstr.s));
}