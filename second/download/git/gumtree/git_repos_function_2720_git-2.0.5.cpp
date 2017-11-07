static void output(struct merge_options *o, int v, const char *fmt, ...)
{
	va_list ap;

	if (!show(o, v))
		return;

	strbuf_grow(&o->obuf, o->call_depth * 2 + 2);
	memset(o->obuf.buf + o->obuf.len, ' ', o->call_depth * 2);
	strbuf_setlen(&o->obuf, o->obuf.len + o->call_depth * 2);

	va_start(ap, fmt);
	strbuf_vaddf(&o->obuf, fmt, ap);
	va_end(ap);

	strbuf_add(&o->obuf, "\n", 1);
	if (!o->buffer_output)
		flush_output(o);
}